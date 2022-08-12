# 第六章 函数

- C++ 允许重载函数，就是不同函数可以使用相同的函数名字，只要参数不同即可。


## 6.1 函数基础

例: 阶乘函数

```
#include<iostream>
using namespace std;

// 阶乘函数
int fact(int n){
    int rs=n;
    while( --n > 0){
        rs *= n;
    }
    return rs;
}
int main(){
    int i;
    cout << "please input an int:" << endl;
    cin >> i;
    cout << i << "!=" << fact(i) << endl;

    return 0;
}

$ g++ a1_fact.cpp 
$ ./a.out 
please input an int:
5
5!=120
```


- 空白形参列表可以留空，为了和C兼容，可以使用 void。

```
void f1(){}  //隐式的定义空形参列表
void f2(void){} //显式的定义空形参列表
```




### 局部变量

C++中，名字有作用域，对象有生命周期 lifetime。要理解这两个概念。

- 名字的作用域是程序文本的一部分，名字在其中可见
- 对象的生命周期是程序执行过程中该对象存在的一段时间。

#### 自动对象

- 块作用域，进入时创建，到达末尾时销毁。这种只存在于块执行期间的变量叫 自动对象 automatic object.
    * 形参是一种自动对象，函数开始时为形参申请存储空间，函数终止，形参销毁。
- 实参用于初始化形参对应的自动对象。
    * 如果变量定义本身不含有初始值，则执行默认初始化。也就是内置类型的未初始化局部变量将产生未定义的值。


#### 局部静态对象 local static object

- 程序第一次执行到时创建并初始化，然后直到程序终止才被销毁，函数结束执行对它没影响。

例：统计该函数被调用多少次了。

```
#include<iostream>
using namespace std;

// 函数被调用次数，局部静态对象
int counter(){
    static int count=0; //函数调用结束，这个值仍然有效
    return ++count;
}

int main(){
    for(int i=0; i<5; i++){
        cout << "call counter: " << counter() << endl;
    }
    return 0;
}

$ g++ a2_local_static.cpp 
$ ./a.out 
call counter: 1
call counter: 2
call counter: 3
call counter: 4
call counter: 5
```

> 如果局部静态变量没有执行初始化，则执行值初始化，内置类型的局部静态变量初始化为0。



### 函数声明

- 函数使用前要声明。函数只能定义一次，但是可以声明多次。
    * 如果一个函数永远也不用，它可以只有声明，没有定义。
- 函数声明不包括函数体，所以形参名字可以省略，但是加上有注意使用者理解。
- 函数三要素（返回类型、函数名、形参类型）描述了函数的接口，说明了调用函数的全部信息。

> 函数原型 function prototype: 函数声明。


#### 在头文件中进行函数声明

- 在头文件中声明，在源文件中定义。符合面向接口的编程思想。

> 函数定义的源文件应该把包含函数声明的头文件，编译器负责检查函数声明和定义是否匹配。








### 分离式编译 separate compilation

- C++支持把程序分成几个文件，每个文件分别编译。
- 分离式编译，提供了多人并行开发的能力，同时也是源代码保密的重要方式。


#### 编译和链接多个源文件

函数声明位于 fact.h 头文件中。
```
$ cat fact.h
int fact(int);
```

函数实现位于 fact.cpp 中
```
$ cat fact.cpp
#include "fact.h"

int fact(int n){
    int rs=1;
    while(n>0){
        rs *= n--;
    }
    return rs;
}
```

使用者名字叫 main.cpp.
```
$ cat main.cpp
#include<iostream>
#include "fact.h"
using namespace std;

int main(){
    int value=0;
    cout << "input an int:" << endl;
    cin >> value;
    cout << value << "!=" << fact(value) << endl;
}
```

直接编译:
```
$ g++ main.cpp fact.cpp #编译出文件 a.out
$ g++ main.cpp fact.cpp -o main #编译出文件 main

执行
$ ./main 
input an int:
6
6!=720
```


- 分离式编译是先编译出中间文件，.obj(win) 或 .o(UNIX) ，后缀名的含义就是该文件包含`对象代码(object code)`
- 如果我们修改了某个文件，只需要修改那个文件即可。其他文件不用重新编译。

分离式编译: 每个文件分别编译
```
$ g++ -c main.cpp #编译出 main.o
$ g++ -c fact.cpp #编译出 fact.o

链接文件
$ g++ main.o fact.o          #默认名字 a.out
$ g++ main.o fact.o -o main  #指定名字 main

$ ./main  #执行程序
input an int:
5
5!=120
```


分离式编译: 混合使用源码和.o进行编译
```
$ g++ -c fact.cpp -o fact.o   # -c 编译，产生 -o fact.o 中间文件，这是一个库文件，他人可能只给我们一个.o文件和.h接口文件。
$ g++ main.cpp fact.o -o main #编译并链接，生成 -o main 文件
```



#### 使用 Makefile 编译

概书没有这部分，稍作介绍。

> Makefile 分别是目标，依赖文件，第二行必须tab开头，是要执行的命令。

```
$ cat Makefile
main: main.o fact.o
	g++ main.o fact.o -o main
main.o: main.cpp
	g++ -c main.cpp -o main.o
fact.o: fact.cpp
	g++ -c fact.cpp -o fact.o
```

执行编译:
```
$ make
g++ -c main.cpp -o main.o
g++ -c fact.cpp -o fact.o
g++ main.o fact.o -o main

$ ./main 
input an int:
5
5!=120
```









## 6.2 参数传递

> 形参初始化的机理与变量初始化一样。

形参与实参的交互：

- 当形参是引用类型时，我们说它对应的实参被 引用传递(passed by reference) 或者 函数被传引用调用(called by reference)。引用形参是它对应的实参的别名。
- 当实参的值拷贝给形参时，形参和实参是2个相互独立的对象。我们说这样的实参被 值传递(passed by value) 或者 函数被传值调用(called by value)。


### 按值传递

按值传递不影响原来的实参。不过指针是个例外。

#### 指针形参

指针指向的是变量的内存地址，如果按地址修改，则影响地址中保存的数据。如果仅仅修改指针自己，则不影响实参。

```
#include<iostream>
using namespace std;

// 指针形参
void change(int *p){
    *p *= 2; //指针指向的整数值 改变，指针实参不变
}

void change2(int *p){
    p=0; // 指向的整数值不变，指针实参也不变。
}

int main(){
    int i=1024;
    int *ptr=&i;
    cout << "1 ptr=" << ptr << ", value *ptr=" << *ptr <<  endl;

    // change value
    change(ptr);
    cout << "2 ptr=" << ptr << ", value *ptr=" << *ptr <<  endl;

    //change 2
    change2(ptr);
    cout << "3 ptr=" << ptr << ", value *ptr=" << *ptr <<  endl;

    return 0;
}

$ g++ a4_parameter_ptr.cpp 
$ ./a.out 
1 ptr=0x7fff535ed02c, value *ptr=1024
2 ptr=0x7fff535ed02c, value *ptr=2048
3 ptr=0x7fff535ed02c, value *ptr=2048
```

> C语言经常使用指针类型的形参访问函数外部的对象。C++中，建议使用引用类型的形参代替指针。




### 传引用参数

引用就是原变量的别名。

对引用的操作，实际上是作用在引用所引的对象上。

```
#include<iostream>
using namespace std;

//按引用传递
void change(int &ref){
    ref *= 2; //改变了 ref 所引用的对象
}

int main(){
    int num=10;
    cout << num << endl;
    
    change(num);
    cout << num << endl;
    
    return 0;
}

$ g++ a5_para_by_ref.cpp 
$ ./a.out 
10
20
```


#### 使用引用避免拷贝

- 拷贝大的类类型对象或者容器对象比较低效，甚至有的类类型（包括IO类型在内）不支持拷贝操作。这是使用引用的理由。

> 如果函数无需改变引用形参的值，最好将其声明为常量引用 `const string &s1`。


例：比较长字符串的长度的函数。

- 字符串比较长时，要尽量避免拷贝，推荐使用引用传递参数。
- 又因为比较长度无需改变字符串，所以定义为对常量的引用。

```
#include<iostream>
#include<string>
using namespace std;

//比较长字符串的长度的函数
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

int main(){
    string str1="hi";
    string str2="hello!";

    cout << str1 << " is shorter than " << str2 << "?" << endl;

    string result = isShorter(str1, str2)==1 ? "yes": "no";
    cout << result << endl;
    return 0;
}


$ g++ a6_para_by_ref2.cpp 
$ ./a.out 
hi is shorter than hello!?
yes
```


#### 使用引用形参返回额外信息

例: 如何从一个函数中获取某个字符首次出现的位置和该字符出现的总次数？

- 返回值返回一个信息，引用形参获取另一个信息。

```
#include<iostream>
using namespace std;

//通过引用形参获取额外信息

string::size_type find_char(const string &s, char ch, 
                string::size_type &cnt){
    auto ret= s.size(); //字符长度
    cnt=0; //字符出现的总次数
    for(decltype(ret) i=0; i<s.size(); ++i){
        if(s[i]==ch){
            ++cnt; //出现次数计数器
            if(ret == s.size()){ //这个初始值是比最大下标还大1的，没改变就表示没找到。
                ret =i; //第一次出现的位置
            }
        }
    }
    return ret;
}

int main(){
    string s2="This is a book.";    
    cout << "Input a char:" << endl;
    char char2;
    cin >> char2;

    //开始统计
    string::size_type totalCnt=0;
    string::size_type start=find_char(s2, char2, totalCnt);
    // 输出: 字符出现总次数，首次出现的下标
    cout << endl;
    cout << "the char:" << char2 << endl;
    cout << "in string:" << s2 << endl;
    cout << "Total count:" << totalCnt << ", first index:" << start << endl;

    return 0;
}

$ g++ a7_get_info_by_ref.cpp 
$ ./a.out 
Input a char:
s

the char:s
in string:This is a book.
Total count:2, first index:3
```








### const 形参和实参

- 顶层 const 作用于对象本身

```
const int i2=20; //不能改变 i2 的值，是顶层const
int i=i2; //正确，拷贝时忽略它的顶层const

int *const p=&i; //const是顶层的，不能给p赋值，只能初始化
*p=0;  //正确，通过p改变其对象的内容是允许的，现在i的值是0
```

- 当形参是顶层const时，传给它常量或者非常量对象都是可以的。
    * `void fn(const int i){ /*fn 内能读取i，但是不能向i写值*/}`
    * 调用函数fn时，可以传入 `const int` 也可以传入 `int`

- 新定义的函数与已有函数原型只相差一个const是不行的：函数原型作比较时忽视顶层const。

```
void fn(const int i){}
void fn(int i){} //错误，重复定义了 fn(int)
```



#### 指针或引用形参与 const

- 可以使用非常量初始化底层const对象，反过来则不行；
- 一个普通的引用，必须用同类型的对象初始化。

```
$ cat a8_const_para_init.cpp
#include<iostream>
using namespace std;

// const 与非 const 的初始化
int main(){
    int i=20;
    const int *cp=&i; //正确，但是cp不能改变i
    const int &r=i; //正确，但是r不能改变i
    const int &r2=40; //正确

    //int *p=cp; //错误，p 和 cp 类型不同
    //error: invalid conversion from ‘const int*’ to ‘int*’

    //int &r3=r; //错误，r3和r类型不同
    //error: binding reference of type ‘int&’ to ‘const i discards qualifiers

    //int &r4=40; //错误，不能用字面量初始化一个非常量引用
    // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

    return 0;
}
```



- 同样的规则适用于参数传递
    * 要想调用引用版本的函数，只能使用int类型的对象，而不能使用字面量、求值结果为int的表达式、需要转换的对象或者 const int 类型的对象。
    * 想要调用指针版本的函数，只能使用 int*。
    * 我们能传递一个字符串字面量作为某函数形参，是因为该引用形参是const引用，而C++允许使用字面量初始化常量引用。


//todo hard 很难，这里要反复看。


```
$ cat a9_const_para_init2.cpp
#include<iostream>
using namespace std;

//const 用于参数传递
void reset(int *p){
    *p = 1;
}

void reset(int &r){
    r = 0;
}

void reset(string &r){
    r = "";
}

void reset2(const string &r){
    cout << "can not change " << r << endl;
}

int main(){
    int i=15;
    const int ci=i;
    string::size_type ctr=0;

    reset(&i); //调用形参类型是 int* 的reset 函数
    //reset(&ci); //错误，不能用指向 const int 的指针初始化 int *
    //error: no matching function for call to ‘reset(const int*)’

    reset(i); //调用形参类型是 int & 的reset 函数

    //reset(ci); //错误: 不能把普通引用绑定到 const 对象 ci 上
    // error: binding reference of type ‘int&’ to ‘const int’ discards qualifiers

    //reset(40); // 错误：不能把普通引用绑定到字面量(右值)上
    // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

    //reset(ctr); //错误，类型不匹配，ctr是无符号类型
    // error: no matching function for call to ‘reset(std::__cxx11::basic_string<char>::size_type&)’

    //reset("hello");     // error: invalid conversion from ‘const char*’ to ‘int’

    reset2("hello");     // reset2 的第一个形参是对常量的引用

    string s2="hi"; 
    reset(s2); //字符串对象的引用

    return 0;
}
```




#### 尽量使用常量引用

- 把函数不会改变的形参定义成（普通）引用是一种常见错误：函数调用者误以为可以修改实参的值。
- 使用引用而非常量引用，会极大的限制函数能接受的实参类型：不能把const对象、字面值或者需要类型转换的对象传递给普通的引用形参。


> 一个难察觉的错误: 就是形参是引用，则传入字面量时报错; 如果形参是常量引用，则可以传入字面量。

```
//不良设计，第一个形参应该是 const string&
string::size_type find_char(string &s, char c, string::size_type &cnt);

//则只能接收string对象，传递字符串字面量则编译报错
find_char("Hello", 'o', ctr);
```


> 另一个更难察觉的错误：加入其它函数（正确的）将他们的形参定义成常量引用，则函数内调用（无const的版本的）find_char() 将编译错误。

```
#include<iostream>
using namespace std;

// 形参尽可能使用常量引用

string::size_type find_char(const string &s, char ch, string::size_type &cnt){ //version1: 提倡
//string::size_type find_char(string &s, char ch, string::size_type &cnt){ //version2
    // 返回符号ch首次出现的位置，通过引用获取符号ch出现的总次数cnt
    string::size_type pos=s.size();
    cnt=0;
    for(string::size_type i=0; i<s.size(); i++){
        if(s[i] == ch){
            ++cnt; //计数器
            if(pos==s.size()){
                pos=i;
            }
        }
    }
    return pos;
}


// 如果s2的结尾有且仅有一个句号，则s2是一个句子
bool is_sentence(const string &s2){
    string::size_type count=0;
    return find_char(s2, '.', count) == s2.size()-1 && count ==1;
}


int main(){
    string s2="hello, world.";
    char cha='o';
    string::size_type count=0;
    string::size_type index=find_char(s2, cha, count);
    //string::size_type index=find_char("good", cha, count); //可以传入字面量 only for version1.
    //
    cout << "str: " << s2 << endl;
    cout << "char:" << cha << endl;
    cout << "first index:" << index << ", count:" << count << endl;

    bool isSts=is_sentence(s2); //只支持const的 version1，否则报错
    string msg = (isSts? "is":"is not") + string(" a sentence.");
    cout << s2 << msg << endl;

    return 0;
}


$ g++ a10_const_para_init3.cpp 
$ ./a.out 
str: hello, world!
char:o
first index:4, count:2
hello, world!is not a sentence.
```








### 数组形参

- 数组不允许拷贝，所以无法值传递。
- 数组通常会转为指针，所以传数组时实际传递的是一个指向数组首元素的指针

> 尽管不能值传递，我们可以把形参写成类似数组的形式。程序员保证下标不越界。

```
// 尽管形参不同，但是这三个函数是等价的，每个函数的唯一形参都是 `const int *` 类型的。
void print(const int *);
void print(const int[]);  //函数的意图是作用于一个数组
void print(const int[10]);  //这里的维度是我们期望的维度，实际不一定


// 编译器执行时，只检查传入的参数是否是 const int* 类型的
int i=0, j[2]={10,20};
print(&i); //正确，&i 的类型是 int*
print(j); // 正确，j的类型转成 int* 指向 j[0]
```

例:

```
#include<iostream>
using namespace std;

//数组作为参数
void print(const int *p){
    cout << p << ", *p="<< *p<< endl;
};
void print2(const int arr[]){  //函数的意图是作用于一个数组
    cout << arr << ", arr[0]="<< arr[0] << endl;
}
void print3(const int arr[10]){  //这里的维度是我们期望的维度，实际不一定
    cout << arr << ", arr[0]="<< arr[0] << endl;
}

int main(){
    int arr2[]={10,20,30};
    int *ptr=arr2;

    print(ptr);
    print2(arr2);
    print3(ptr);

    return 0;
}

$ g++ a11_para_array.cpp 
$ ./a.out 
0x7ffc9c94c21c, *p=10
0x7ffc9c94c21c, arr[0]=10
0x7ffc9c94c21c, arr[0]=10
```

函数内部不知道数组的长度。调用者应该额外提供这个信息。

管理指针形参有三种常用技术：




#### 使用标记指定数组长度

- 数组本身包含一个结束标记，貌似只有C风格的字符串。
- 不适合int数组。

```
#include<iostream>
using namespace std;

// 数组自带结束标记：C风格字符串
void print(const char *cp){
    if(cp) // 非空指针
        while(*cp) //不能是结尾 '\0'
            cout << *cp++; //输出当前字符，并指针向后移动一位
}

int main(){
    char s2[]="this is a book.";
    print(s2);

    cout << endl;
    return 0;
}

$ g++ a12_para_array_withEnd.cpp 
$ ./a.out 
this is a book.
```


#### 使用标准库规范

- 传递指向数组首元素和尾后元素的指针。

```
#include<iostream>
using namespace std;

// 传递指向首元素和尾后元素的指针/迭代器
void print(const int *begin, const int *end){
    //输出之间的值
    while(begin<end)
        cout << *begin++ << endl; // 输出当前值，并后移一位
}

int main(){
    int arr[]={10,20,30,40};
    //print(begin(arr), end(arr));
    //print(arr, end(arr)); //效果同上
    print(arr, arr + sizeof(arr)/sizeof(int) ); //效果同上

    return 0;
}

$ g++ a13_para_array_withIter.cpp 
$ ./a.out 
10
20
30
40
```


#### 显式传递一个表示数组大小的形参

- 这是过去C程序中经常使用的方法。

```
#include<iostream>
using namespace std;

// 显式传递一个数组长度参数
void print(int arr[], int N){
    for(int i=0; i<N; i++){
        cout << arr[i] << endl;
    }
}

int main(){
    int arr2[]={10,20,30};
    //print(arr2, sizeof(arr2)/sizeof(int));
    print(arr2, end(arr2) - begin(arr2) ); //效果同上
    return 0;
}

$ g++ a14_para_array_withN.cpp 
$ ./a.out 
10
20
30
```



#### 数组形参和 const 

- 当数组不需要对数组写操作时，数组形参应该定义成指向const 的指针。
- 只有确实要写时，才把形参定义成 指向非常量的指针。


#### 数组引用形参

- C++ 允许将变量定义为数组的引用。见 3.2.1节P101: 

```
int *ptrs[10]; // 这是一个数组，10个元素，每个元素都是一个指向int的指针
int *(&arr)[10] = ptrs; //arr 是数组的引用，该数组含有10个指针
// 从内向外阅读
// &arr 是一个引用，看右侧[10] 是一个10元素数组，左侧 int * 每个元素都是指向整数的指针。
```

> 注意，&arr两端的圆括号不能省略！

```
f(int &arr[10])   //错误：将arr声明成了引用的数组
f(int (&arr)[10]) //正确：arr是具有10个整数的整型数组的引用
```

例: 缺点是，只能传入大小为固定值的数组。

```
#include<iostream>
using namespace std;

//数组引用形参 fn(int (&arr)[3]) 注意，(%arr) 的圆括号不能省略
//void change(int &arr[3]){ //error: declaration of ‘arr’ as array of references
void change(int (&arr)[3]){
    cout << sizeof(arr)/sizeof(int) << endl; //能获取长度
    arr[0]=1024; //能修改数组的值
}


int main(){
    int i1=1, i2=2, i3=3, arr2[]={10,20,30};
    change(arr2);
    cout << arr2[0] << endl;

    return 0;
}

$ g++ a15_para_arrRef.cpp 
$ ./a.out 
3
1024
```

- P576, 16.1.1 将要讲解如何编写这个函数，可以给引用的形参传递任意大小的数组。



#### 传递多维数组

- 给多维数组传递参数，实质上是传递的指向第一个元素的指针。
- 而数组第二维（及之后的维度）是数组的一部分，不能省略。

```
#include<iostream>
using namespace std;

//传递多维数组，要传递第二维及之后的维度
//void print(int (*arr)[2], int rowSize){
void print(int arr[][2], int rowSize){ //等价形式
    for(int i=0; i<rowSize; ++i){
        for(int j=0; j<2; ++j){
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}



int main(){
    int arr2[3][2]={ {1,2}, {10,20}, {100,200} };
    print(arr2, 3);

    return 0;
}

$ g++ a16_para_multi_arr.cpp 
$ ./a.out 
1       2
10      20
100     200
```


> 再次强调， *arr 两端的圆括号必不可少！

```
int *matrix[10]; //10个指向int的指针构成的数组
int (*matrix)[10]; //指向含有10个整数的数组的指针


void print( int (*matrix)[10], int rowSize){} 
//等价于
void print( int matrix[][10], int rowSize){}  //形参看起来是一个二维数组，实际上是指向含有10个整数的数组的指针。
```






### main: 处理命令行选项

> 怎么向程序传参数？通过main函数的2个参数。

```
int main(){} //之前我们一直使用空参数的main

// 假设编译后的程序是 a.out, 传参数格式：
$ a.out -d -o ofile data0 #该命令通过2个可选 形参传递给main函数

int main(int argc, char *argv[]){}
// 第一个是argc参数个数，第二个 argv 是一个数组，其元素指向C风格的字符串的指针。

// 因为第二个形参是数组，所以也可写写成
int main(int argc, char **argv){} //其中 argv 是指针，指向 char*.
```

当实参传递给main函数后，argv 的第一个元素指向程序的名字或者一个空字符串，接下来的元素依次传递命令行提供的实参，最后一个指针之后的元素值保证是0.

```
#include<iostream>
using namespace std;

//main 函数接受参数
int main(int argc, char **argv){
    // 打印各个参数
    cout << "argc=" << argc << endl;
    
    int i=0;
    while (argv[i] != 0){
        cout << "argv[" << i << "]=" << argv[i] << endl;
        i++;
    }
    cout << endl;

    while (*argv != 0){
        cout << "*argv=" << *argv++ << endl;
    }

    return 0;
}

$ g++ b1_main_argv.cpp
$ ./a.out -d -o ofile data0
argc=5
argv[0]=./a.out
argv[1]=-d
argv[2]=-o
argv[3]=ofile
argv[4]=data0

*argv=./a.out
*argv=-d
*argv=-o
*argv=ofile
*argv=data0
```

> 当使用argv 中的实参时，一定要记着可选实参从 argv[1] 开始； argv[0] 是保存程序的名字，不是用户输入的参数。


例：编写一个main，接收两个实参，把它们连成一个string并输出。

```
#include<iostream>
using namespace std;

//
int main(int argc, char *argv[]){
    int i=0;
    while(argv[i] !=0){
        i++;
    }
    if(i<2){
        cout << "Error: must provide 2 parameters" << endl;
        return -1;
    }

    string s1=argv[1];
    string s2=argv[2];
    cout << s1+s2 << endl;

    return 0;
}

$ g++ b2_main_arg_concat.cpp 
$ ./a.out hello world
helloworld
$ ./a.out
Error: must provide 2 parameters
```






### 含有可变形参的函数

- 我们无法提前预知应该接收几个参数时，C++11 新标准提供了2种主要的方法：
    * `initializer_list` 的标准库函数，处理相同的实参类型；
        * 不同类型的实参，可以使用 `可变参数模板` 这种特殊的函数(见P648 16.4节)；
    * 另一种是 `省略符`。


#### initializer_list 形参

- 适用于实参数量未知，但是类型相同的的情况。
- initializer_list 是一种标准库类型，用于表示某种特定类型的数组(见P101, 3.5节)
- initializer_list 类型定义在同名的头文件中。

```
// initializer_list 提供的操作

initializer_list<T> lst; //默认初始化；T类型元素的空数组
initializer_list<T> lst{a,b,c...}; //lst的元素数量和初始值一样多；lst的元素是对应初始值的副本；列表中的元素是const；
lst2(lst); // 拷贝或赋值一个 initializer_list 对象不会拷贝列表中的元素；拷贝后，原始列表和副本共享元素。
lst2=lst; //同上

lst.size(); //元素个数
lst.bebin(); //返回指向lst中首元素的指针
lst.end(); //返回指向lst中尾后元素的指针
```


- 和 vector 一样，是一种模板类型。定义时，必须说明列表中的元素的类型：

```
initializer_list<string> ls; //元素类型是string
initializer_list<int> li; //元素类型是int
```

- 和 vector 不同的是，initializer_list 对象中的元素永远是常量值，我们无法改变 initializer_list 中的元素的值。
- 可以使用迭代器 x.begin() 和 x.end() 或者 范围 for 遍历 initializer_list 对象。

```
#include<iostream>
using namespace std;

// initializer_list 获取不定数量参数，类型相同
void error_msg(initializer_list<string> il){
    for(auto beg=il.begin(); beg!=il.end(); ++beg){
        cout << *beg << " ";
    }
    cout << endl;
}


int main(){
    //测试错误信息
    string expected="hello";
    string actual;
    cout << "Please input hello, other word may produce an error message:" << endl;
    cin >> actual;

    if(expected != actual){
        error_msg({"functionX error:", expected, actual}); //注意，字符串要写到花括号中
    }else{
        error_msg({"functionX", "okey"}); //第一次调用传入3个值，第二次调用传入2个值
    }

    return 0;
}

$ g++ b3_main_initializer_list.cpp 

$ ./a.out 
Please input hello, other word may produce an error message:
hello
functionX okey 

$ ./a.out 
Please input hello, other word may produce an error message:
hi
functionX error: hello hi
```

含有 initializer_list 形参的函数也可以同时有其他形参。比如，调试系统可用 ErrCode 类来表示不同类型的错误：

```
#include<iostream>
using namespace std;

// ErrCode 类表示不同类型的错误
//注：作者这里没有说 ErrCode 是啥，也没搜到线索，我推测是一个自定义类，简陋实现如下
class ErrCode{
    private:
        int num=0;
    public:
        ErrCode(int i){
            num=i;
        }
        string msg(){
            if(num==0){
                return "success";
            }else{
                return "InputError";
            }
        }
};

void error_msg(ErrCode e, initializer_list<string> il){
    //先打印错误
    cout << e.msg() << ": ";

    for(const auto &elem: il){
        cout << elem << " ";
    }
    cout << endl;
}

int main(){
    //测试错误信息
    string expected="hello";
    string actual;
    cout << "Please input hello, other word may produce an error message:" << endl;
    cin >> actual;

    if(expected != actual){
        error_msg(ErrCode(42), {"functionX error:", expected, actual}); //注意，字符串要写到花括号中
    }else{
        error_msg(ErrCode(0), {"functionX", "okey"}); //第一次调用传入3个值，第二次调用传入2个值
    }

    return 0;
}

$ g++ b4_main_initializer_list_ErrCode.cpp

$ ./a.out 
Please input hello, other word may produce an error message:
hello
success: functionX okey 

$ ./a.out 
Please input hello, other word may produce an error message:
hi
InputError: functionX error: hello hi
```



#### 省略符形参

- 为了方便C++程序访问C代码而设置的形参，这些代码使用了名为 varargs 的C标准库功能。
- 通常，省略符形参不能用于其他目的，C编译器文档会描述如何使用 varargs。

> 省略符形参仅仅用于C和C++通用的类型。大多数类 类型的对象在传递给省略符形参时都无法正确拷贝。

```
// 省略符形参只能是形参列表的最后一个位置。也就两种形式
void fn(para_list, ...); //前面的形参传递过来会进行类型检查，省略符形参无须类型检查。
void fn(...);
```

















## 6.3 返回类型和return语句

- return 是函数终止并把控制权交给调用者的地方。共2种形式：

```
return;
return expression;
```


### 无返回值函数

对于返回值为void的函数，如果想在中间提前返回，则可以使用 `return;`，类似 break 语句可以退出循环，这个是退出函数。

例: 使用引用形参，写一个函数交换2个值。

```
#include<iostream>
using namespace std;

// 返回空
void swap(int &i1, int &i2){
    // 如果相等，直接返回
    if(i1==i2)
        return;
    // 如果不等，则交换值
    int tmp=i1;
    i1=i2;
    i2=tmp;
    //此处无须显示return语句。
}

int main(){
    int x=10, y=-80;
    cout << "x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "x=" << x << ", y=" << y << endl;

    return 0;
}

$ g++ b5_return.cpp 
$ ./a.out 
x=10, y=-80
x=-80, y=10
```


 一个返回值是 void 的函数也可以使用第二种return语句，只不过这个语句必须是一个返回void 的函数。

```
#include<iostream>
using namespace std;

// 返回值是void的函数也可以使用 return expression; 只不过expression必须是返回void的函数。

void logs(int x){
    cout << "this is fn1(x), x=" << x << endl;
    return;
}

void fn(int a){
    return logs(a);
}

int main(){
    fn(500);
    return 0;
}

$ g++ b6_return_void.cpp 
$ ./a.out 
this is fn1(x), x=500
```




### 有返回值的函数

尽管c++不能保证结果正确，但是可以保证每个return返回的类型正确。

```
#include<iostream>
using namespace std;

// 如果for循环中有return，则for后也要有return语句，不是所有编译器都能是识别这一点。
int getIndex(int arr[], int value){
    for(int i=0; i<4; i++){
        if(arr[i] == value){
            return i;
        }
    }

    //return -1; //for后的 return 是必须的！
}

int main(){
    int arr2[]={10,20,30,40};
    cout << getIndex( arr2, 30) << endl;
    cout << getIndex( arr2, 35) << endl; //如果 getIndex 没有最后的 return -1; 则找不到时返回异常值: 40
    return 0;
}

$ g++ b7_return_in_for.cpp 
b7_return_in_for.cpp: In function ‘int getIndex(int*, int)’:
b7_return_in_for.cpp:13:1: warning: control reaches end of non-void function [-Wreturn-type]
   13 | }
      | ^

$ ./a.out 
2
40
```




#### 值是如何被返回的

- 返回一个值的方式和初始化一个变量或形参的方式完全相同：返回的值用于初始化调用点的要给临时量，该临时量就是函数调用的结果。

> 注意：函数返回局部变量时的初始化规则：

例: 根据计数器，确定单词的单数和复数形式。

```
#include<iostream>
using namespace std;

//根据计数器，返回单复数
string make_plural(size_t ctr, const string &word, const string &ending){
    return (ctr>1) ? word+ending : word;
    //该函数的返回值是string，意味着返回值将被拷贝到调用点。
    //因此，该函数将返回word的副本或者一个未命名的临时string对象，该对象的内容是 word 和 ending 的和。
}

//如果函数返回一个引用，则该引用仅是它所引用对象的一个别名。
//返回string对象中较短的那个
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
    // 形参和返回类型都是 const string 引用，不管是调用函数还是返回结果都不会真正拷贝string 对象
}


int main(){
    string s1="hi";
    string s2="dog";
    string ending="s";

    //返回拷贝，则地址改变
    string s3=make_plural(3, s2, ending);
    string s4=make_plural(1, s2, ending);
    cout << "addr: &s2=" << &s2 << ", value s2=" << s2 << endl;
    cout << "addr: &s3=" << &s3 << ", value s3=" << s3 << endl;
    cout << "addr: &s4=" << &s4 << ", value s4=" << s4 << endl;
    cout << endl;

    // 传入引用，返回引用，如果用同类型接收返回值，则地址不变
    const string &s5=shorterString(s1, s2); //必须使用相同的类型接收返回值(const + &)，否则还可能继续拷贝变量（string s5 OR const string s5）
    cout << "addr: &s1=" << &s1 << ", value s1=" << s1 << endl;
    cout << "addr: &s5=" << &s5 << ", value s5=" << s5 << endl;

    return 0;
}


$ g++ b8_return_word.cpp 
$ ./a.out 
addr: &s2=0x7fff8e3a8290, value s2=dog
addr: &s3=0x7fff8e3a82d0, value s3=dogs
addr: &s4=0x7fff8e3a82f0, value s4=dog

addr: &s1=0x7fff8e3a8270, value s1=hi
addr: &s5=0x7fff8e3a8270, value s5=hi
```




#### 不要返回局部对象的引用或指针

函数调用结束，占用的内存将被释放。如果返回局部对象的引用或指针，则该区域将不再是有效内存区域。

```
#include<iostream>
using namespace std;

// 返回函数局部变量的指针或引用，将报错
int *fn1(){
    int i=5;
    return &i;
    // warning: address of local variable ‘i’ returned
}

int main(){
    int *p=fn1();
    cout << *p << endl; // 运行时错误: Segmentation fault (core dumped)

    return 0;
}


$ g++ b9_return_local_var.cpp 
b9_return_local_var.cpp: In function ‘int* fn1()’:
b9_return_local_var.cpp:7:12: warning: address of local variable ‘i’ returned [-Wreturn-local-addr]
    7 |     return &i;
      |            ^~
b9_return_local_var.cpp:6:9: note: declared here
    6 |     int i=5;
      |         ^
$ ./a.out 
Segmentation fault (core dumped)
```


返回引用的错误例子类似：

```
#include<iostream>
using namespace std;

//返回局部变量的值的引用，也会报错
const string &manip(int signal){
    string ret;
    // 改变一下rect的值
    if(signal==0)
        ret =0;
    else
        ret="hi";
    
    if( ! ret.empty() )
        return ret;  //错误：返回局部对象的引用
        // warning: reference to local variable ‘ret’ returned
    else
        return "Empty"; //错误："Empty" 是一个局部临时量
        // warning: returning reference to temporary
}


int main(){
    const string s0=manip(0);
    const string s1=manip(1);

    //cout << s0 << endl;
    //cout << s1 << endl;

    return 0;
}


$ g++ b10_return_local_var_ref.cpp
$ ./a.out 
Segmentation fault (core dumped)
```


> 要想返回安全的引用，我们不妨提问：引用所引的是函数之前已经存在的那个对象？





#### 返回类类型的函数和调用运算符

- 调用运算也符合左结合律。
- 调用运算的优先级与 点和箭头元素符相同。


```
// 调用string 对象的size成员函数。
auto sz= shorterString(s1, s2).size();
```



#### 引用返回左值

- 调用一个返回引用的函数得到左值，其他返回类型得到右值。
- 可以像其他左值那样使用返回左值的函数。特别的，我们能为返回类型是非常量引用的函数的结果赋值。

> 把函数调用写到赋值语句的左侧，看起来很奇怪，但左值就是这么用的。左值可以放到赋值运算的左侧。

```
#include<iostream>
using namespace std;

//为返回左值的函数结果赋值，不能是常量
char &get_val(string &str, string::size_type index){
    return str[index];
}


int main(){
    string s1="hello";
    cout << "1 &s1=" << &s1 << endl;

    string &s2=s1;
    cout << "2 &s2=" << &s2 << endl; //引用，就是别名，所以指向的地址是相同的。


    // 无法获取返回的引用的地址 //todo why?
    cout << "3 get_val(s1, 0): " << get_val(s1, 0) << endl;
    cout << "4 &get_val(s1, 0): " << &get_val(s1, 0) << endl;
    //赋值给变量也不行 //todo why?
    char &r1=get_val(s1, 0); // 加const也不报错
    cout << "5 r1=" << r1 << endl; //拿不到地址
    cout << "6 &r1=" << &r1 << endl;
    //通过修改r1修改s1的值
    r1='a';
    cout << "7 s1=" << s1 << endl;

    //通过左值改变原始字符串
    cout << "8 s1=" << s1 << endl;
    get_val(s1, 0)='H'; //将 s1[0] 的值改为H
    cout << "9 s1=" << s1 << endl;

    return 0;
}


$ g++ b11_return_left_value.cpp 
$ ./a.out 
1 &s1=0x7fff372d4e40
2 &s2=0x7fff372d4e40
3 get_val(s1, 0): h
4 &get_val(s1, 0): hello
5 r1=h
6 &r1=hello
7 s1=aello
8 s1=aello
9 s1=Hello
```

如果返回类型是常量引用，则不能给调用的结果赋值。

```
shorterString("hi", "bye") = "X"; //错误：返回值是一个常量
```



#### 列表初始化返回值

- C++11新标准，函数可以返回花括号包围的值的列表。
- 类似其他返回结果，此处的列表也用来对表示函数返回的临时量进行初始化。
    * 如果列表为空，临时量执行值初始化；
    * 非空，返回的值由函数的返回类型决定。

例：6.2.6节的 error_msg 函数，其输入是一组可变数量的string 实参，输出是这些输入string对象组成的错误信息。
本题，我们返回一个vector对象，用它存放表示错误信息的string 对象。

```
#include<iostream>
#include<vector>
using namespace std;

//返回列表初始化值的函数
vector<string> process(){
    string expected = "hello";
    string actual;
    cout << "Please input hello, otherwise may produce an err msg:" << endl;
    cin >> actual;
    //开始判断
    if( expected.empty())
        return {}; //返回一个空vector 对象
    else if(expected == actual)
        return {"functionX", "okey"}; //返回列表初始化vector
    else 
        return {"functionX", expected, actual};
}

int main(){
    vector<string> msg=process();

    for(auto i: msg)
        cout << i << " ";
    cout << endl;

    return 0;
}

$ g++ b12_return_list.cpp

$ ./a.out 
Please input hello, otherwise may produce an err msg:
hi
functionX hello hi 

$ ./a.out 
Please input hello, otherwise may produce an err msg:
hello
functionX okey 
```

- 如果函数返回的是内置类型，则花括号包围的列表最多包含一个值，而且该值占用的空间不能大于目标类型的空间。
- 如果函数返回的是 类 类型，有类本身定义初始值如何使用。

```
#include<iostream>
using namespace std;

//返回内置类型的 列表初始化值
int init(int x){
    //return {x, 100}; //error: cannot convert ‘<brace-enclosed initializer list>’ to ‘i in return
    return {x};
}

int main(){
    int a=init(10);
    cout << a << endl;
    return 0;
}

$ g++ b13_return_list2.cpp 
$ ./a.out 
10
```





#### 主函数 main 的返回值

- main 函数可以没有返回值，隐式在末尾添加 `return 0;`
- 返回0表示执行成功，其他值表示失败。
    * 其中非0值与机器有关。为了与机器无关，cstdlib头文件定义了2个预处理变量，EXIT_FAILURE / EXIT_SUCCESS。
    * 预处理变量，不能加std::，也不能在using 声明中出现。

```
#include<iostream>
using namespace std;

int main(int argc, char **argv){
    int i=argc;
    cout << "Parameter number: " << i-1 << endl;

    //不输入参数则报错
    if(i>1){
        cout << "ok" << endl;
        return EXIT_SUCCESS; //定义在 cstdlib 头文件中
    }else{
        cout << "Error: no parameter" << endl;
        return EXIT_FAILURE; //定义在 cstdlib 头文件中
    }
}


$ g++ b14_EXIT.cpp 
$ ./a.out 
Parameter number: 0
Error: no parameter
$ echo $?
1

$ ./a.out 1 2 3
Parameter number: 3
ok
$ echo $?
0
```




#### 递归

- 如果一个函数调用了自己，直接或间接，都叫递归函数(recursive function).

例: 递归实现阶乘。

```
#include<iostream>
using namespace std;

// 递归求阶乘
long fact(int n){
    long result=1;
    if(n<=1)
        return 1;
    return n*fact(n-1);
}

int main(){
    int i=5;
    cout << i << "!=" << fact(i) << endl;

    return 0;
}

$ g++ b15_recursive.cpp 
$ ./a.out 
5!=120
```

- 递归函数中，一定要有退出条件，就是某条路径能达到，并且不包含递归调用。
    * 否则，递归将会无限循环，直到程序栈空间耗尽。我们说这种函数含有 递归循环(recursion loop)。
- main 函数不能调用它自己。



例：(其他书的例子) 递归调用是在栈上创建新的函数空间，里面的每个n都是新函数空间的n。

```
#include<iostream>
using namespace std;

//显示递归函数中的变量的地址
void showAddr(int n){
    cout << "Before " << n << ", addr:" << &n << endl;
    if(n<4)
        showAddr(n+1);
    cout << " After " << n << ", addr:" << &n << endl;
}

int main(){
    showAddr(0);
    return 0;
}


$ g++ b16_recursion_addr.cpp 
$ ./a.out 
Before 0, addr:0x7ffdbecddd9c
Before 1, addr:0x7ffdbecddd7c
Before 2, addr:0x7ffdbecddd5c
Before 3, addr:0x7ffdbecddd3c
Before 4, addr:0x7ffdbecddd1c
 After 4, addr:0x7ffdbecddd1c
 After 3, addr:0x7ffdbecddd3c
 After 2, addr:0x7ffdbecddd5c
 After 1, addr:0x7ffdbecddd7c
 After 0, addr:0x7ffdbecddd9c
```

我们看到，相同的n值表示同一个函数栈，其内存地址是相同的。










### 返回数组指针

- 因为数组不能被拷贝，所以函数不能返回数组。不过，函数可以返回数组的指针或引用。
- 定义一个返回数组的指针或引用的函数比较繁琐，简化方法是使用类型别名。


```
typedef int arrT4[4]; //arrT4是一个类型别名，表示含有4个整数的数组: int [4]

using arrT4_2= int [4]; //arrT4_2 同上
arrT4* func(int i); //函数 func 返回一个指向含有10个整数的数组的指针 
//todo 这是不是会报错？返回的指针指向谁？
```

其中 arrT4 是含有4个整数的数组的别名。因为函数无法返回数组，但是可以返回指向数组的指针。


例: 简化写法的用法。

```
#include<iostream>
using namespace std;

// 指向数组的指针
int get_by_index(int (*p)[4], int index){
    return (*p)[index];
}

// 简化版
typedef int arrT4[4]; //arrT4是一个类型别名，表示含有4个整数的数组: int [4]
int get_by_index2(arrT4 arr, int index){
    return arr[index];
}

using arrT4_2= int [4]; //arrT4_2 同上
int get_by_index3(arrT4_2 arr, int index){
    return arr[index];
}

int get_by_index4(arrT4_2 *p, int index){
    return (*p)[index];
}

int main(){
    int arr[]={50,10,20,30};
    cout << get_by_index(&arr, 0) << endl;
    cout << get_by_index2(arr, 0) << endl;
    cout << get_by_index3(arr, 0) << endl;
    cout << get_by_index4(&arr, 0) << endl;

    return 0;
}

$ g++ c1_return_arr_ptr.cpp 
$ ./a.out 
50
50
50
50
```



#### 声明一个返回数组指针的函数

在声明func是不适用类型别名，就要牢记被定义名字后面数组的维度：

```
int arr[10]; //arr是一个含有10个整数的数组
int *p1[10]; //p1是一个数组，含有10个指向int的指针。下标运算优先级 > 解引用符。
int (*p2)[10] = &arr; //p2是一个指针，指向含有10个整数的数组
```

- 同上述声明一样，定义一个返回数组指针的函数，则数组的维度必须跟在函数名字后面。
- 形参列表也跟在函数名字后面，且形参列表优先于数组维度。
- `Type (*functionName(parameter_list))[dimension];`

Type 表示元素的类型，dimension表示数组维度。(*funName(para_list)) 外面的圆括号必须存在，就像上文定义的p2一样，没有圆括号则意思是：返回的是指针的数组。


例: `int (*func(int i))[10];`

- 按照从内到外理解：
    * func(int i) 表示调用func函数需要一个int类型的实参;
    * (*func(int i)) 意味着我们可以对函数调用的结果执行解引用操作，也就是返回的是指针。
    * (*func(int i))[10] 表示解引用func的调用，得到一个10元素数组
    * 最左侧的int表示10元素数组，每个元素的类型是int。

```
#include<iostream>
using namespace std;

int arr[]={0,1,2,3,4};

//返回数组指针
int (*func(int i))[5]{
    arr[0] += i; //使用全局变量

    return &arr;
    //如果不使用全局变量，而是函数内定义 arr，
    //   则运行时报错，编译时警告: warning: address of local variable ‘arr’ returned 
}

int main(){
    int (*p)[5]=func(10); //返回的是指针，获取的也是指针
    const int (*p2)[5]=func(5); //加const后，有啥变化？

    //查看地址
    cout << "1 addr &arr: " << &arr << endl;
    cout << "2 addr p   : " << p << ", &p :" << &p << endl;
    cout << "3 addr p2  : " << p2 << ", &p2:" << &p2 << endl;

    //修改值
    arr[1]=100;
    (*p)[2]=200;
    //(*p2)[2]=700; //加const后不能用该指针修改指向的值，但是可以修改本身的值，是底层const
    //error: assignment of read-only location ‘*(p2 + 40)’
    int arr3[]={0,-1,-2,-3,-4};
    cout << "4 addr p2:" << p2 << endl;
    p2= &arr3; //修改指针本身的值
    cout << "5 addr p2:" << p2 << endl;

    //使用函数作为左值
    (*func(0))[3]=300;
    
    // 遍历
    for(auto i : *p)
        cout << i << " ";
    cout << endl;

    return 0;
}


$ g++ c2_return_ptr.cpp 
$ ./a.out 
1 addr &arr: 0x55c265dad010
2 addr p   : 0x55c265dad010, &p :0x7ffdd3743d88
3 addr p2  : 0x55c265dad010, &p2:0x7ffdd3743d90
4 addr p2:0x55c265dad010
5 addr p2:0x7ffdd3743db0
15 100 200 300 4
```



#### 使用尾置返回类型

- C++11 中，任何函数的定义都能使用 尾置返回(trailing return type) ，但是对于返回类型比较复杂的函数最有效，比如返回类型是数组的指针或数组的引用。
- 尾置返回类型在形参后面，并以 -> 开头。
- 为了表示函数真正的返回类型跟在形参列表之后，我们在本应该出现返回类型的地方放置一个auto

```
// func 接受一个int类型的实参，返回一个指针，该指针指向一个包含10个整数的数组
auto func(int i) -> int (*)[10];
```

例:

```
#include<iostream>
using namespace std;

int arr[]={10,1,2,3,4};

//C++ 尾置返回类型
auto init(int i)-> int (*)[5]{
    arr[i]=0;
    return &arr;
}

int main(){
    int arr2[]={10,20,30,40,50};
    int (*p)[5] = init(4);

    for(auto i : arr){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

$ g++ c3_tailinig_return_type.cpp 
$ ./a.out 
10 1 2 3 0
```




#### 使用 decltype

- 我们知道函数返回的指针将指向哪个数组，就可以使用 decltype  关键字声明返回类型。

例: 函数根据参数i的值，返回2个已知数组中的某一个。

```
#include<iostream>
using namespace std;

//函数返回类型知道是某个数组，就可以使用 decltype 来定义返回类型
int odd[]={1,3,5};
int even[]={2,4,6};

//返回一个指针，指向含有3个整数的数组
decltype(odd) *choose(int i){ 
    //注意：decltype 并不负责把数组类型转换成对应的指针，所以 decltype 的结果是个数组
    // 想要返回指向数组的指针，还要在函数声明前加上*符号
    return i %2 ? &odd : &even;
}

int main(){
    decltype(odd) *arr1=choose(0);
    decltype(odd) *arr2=choose(1);

    cout << odd << endl;
    cout << even << endl;

    cout << arr1 << endl;
    cout << arr2 << endl;

    return 0;
}

$ g++ c4_return_decltype.cpp 
wangjl@YStation:~/data/project/learnCpp/A1/6$ ./a.out 
0x55740f429010
0x55740f429020
0x55740f429020
0x55740f429010
```


练习1：编写一个函数声明，返回一个数组的引用，且该数组包含3个string对象。不要使用尾置返回类型、decltype或者类型别名。

```
#include<iostream>
using namespace std;

//返回数组引用的函数，该数组包含3个 string 对象
string arr0[]={"nothing", "here", "now"};
string arr1[]={"how", "are", "you"};

//string (&getRef)(int index)[3]; //error: ‘getRef’ declared as function returning an array
string (&getRef(int index))[3];

int main(){
    cout << arr0 << endl;
    cout << arr1 << endl;

    for(int i=0; i<2; i++){
        cout << getRef(i) << "\t" << getRef(i)[0]  << endl;
    }
    return 0;
}

string (&getRef(int n))[3]{
    if(n==0)
        return arr0;
    else
        return arr1;
}

$ g++ c5_return_arr_ref.cpp 
$ ./a.out 
0x55a3cc9ca160
0x55a3cc9ca1c0
0x55a3cc9ca160  nothing
0x55a3cc9ca1c0  how
```



练习2: 同上，尝试其他3种声明形式：类型别名、尾置返回类型、decltype关键字

```
#include<iostream>
using namespace std;

//返回数组引用的函数，该数组包含3个 string 对象

string arr0[]={"nothing", "here", "now"};
string arr1[]={"how", "are", "you"};

//0.直接声明
//string (&getRef)(int index)[3]; //error: ‘getRef’ declared as function returning an array
//string (&getRef(int index))[3];

//1. 类型别名
//typedef string ref_str4[3];
//using ref_str4 = string [3];

//ref_str4 &getRef(int i);


//2. 尾置返回类型
//auto getRef(int i) -> string (&)[3];

//3.decltype关键字
decltype(arr0) &getRef(int i);

int main(){
    cout << 3 << endl; //显式表示变化
    cout << arr0 << endl;
    cout << arr1 << endl;

    for(int i=0; i<2; i++){
        cout << getRef(i) << "\t" << getRef(i)[0]  << endl;
    }
    return 0;
}

string (&getRef(int n))[3]{
    if(n==0)
        return arr0;
    else
        return arr1;
}


$ g++ c5_return_arr_ref2.cpp
$ ./a.out 
3
0x55a6e6ad6160
0x55a6e6ad61c0
0x55a6e6ad6160  nothing
0x55a6e6ad61c0  how
```
















## 6.4 函数重载

- 函数名相同、参数列表不同，称为 重载函数(overloaded)
- 编译器根据实参列表推断调用的哪个函数。
- main 函数不能重载。

#### 定义重载函数

例: 一种数据库应用，根据名字、电话、账户号码等查找信息。

```
#include<iostream>
using namespace std;

struct Record{
    char acount;
    int phone;
    string name;
};

Record arr[]={
    {'a', 123, "Tom"},
    {'b', 456, "Lily"},
    {'c', 789, "Lilei"}
};
Record empty={'\0', 0, ""};

//重载函数的声明
Record lookup(const char&); //根据acount查找
Record lookup(const int&); //根据phone查找
Record lookup(const string&); //根据name查找

void print(Record r){
    cout << "struct Record: "<< r.acount << ", " << r.phone << ", " << r.name << endl;
}


int main(){
    char acct='b';
    int phone=123;
    string name="Lilei";

    Record r1=lookup(acct);
    Record r2=lookup(phone);
    Record r3=lookup(name);

    print(r1);
    print(r2);
    print(r3);
    return 0;
}


Record lookup(const char& c){
    cout << ">lookup by account: char " << c << endl;
    for(int i=0; i<3; i++){
        if(arr[i].acount == c)
            return arr[i];
    }
    return empty;
}

Record lookup(const int& n){
    cout << ">lookup by phone: int " << n << endl;
    for(int i=0; i<3; i++){
        if(arr[i].phone == n)
            return arr[i];
    }
    return empty;
}

Record lookup(const string& s){
    cout << ">lookup by name: string " << s << endl;
    for(int i=0; i<3; i++){
        if(arr[i].name == s)
            return arr[i];
    }
    return empty;
}


$ g++ d1_overloaded.cpp 
$ ./a.out 
>lookup by account: char b
>lookup by phone: int 123
>lookup by name: string Lilei
struct Record: b, 456, Lily
struct Record: a, 123, Tom
struct Record: c, 789, Lilei
```



#### 判断2个形参的类型是否相等

- 形参的名字可以忽略。


#### 重载与const形参

顶层const不影响传入函数的对象。

//todo hard.


```
Record lookup(Phone);
Record lookup(const Phone); //重新声明了 Record lookup(Phone)

Record lookup(Phone *);
Record lookup(Phone* const); //重新声明了 Record lookup(Phone *)
```

例1: 一个拥有顶层const的形参无法与另一个没有顶层const的形参区分开来

```
#include<iostream>
using namespace std;

int lookup(int);
int lookup(const int); //重新声明了 int lookup(int)

int lookup(int *);
int lookup(int* const); //重新声明了 Record lookup(int *)


int arr[]={10,11,12,30,14,50};

int main(){
    int a2=12;
    int i2=lookup(a2);
    cout << "index of " << a2 << " is " << i2 << endl;

    return 0;
}

int lookup(int value){
    for(int i=0; i<6; i++){
        if(arr[i]==value)
            return i;
    }
    return -1;
}

/* 声明不报错，但是定义时报错
//error: redefinition of ‘int lookup(int)’
int lookup(const int value){
    return -1;
}
*/

$ g++ d2_overload_const.cpp 
$ ./a.out 
index of 12 is 2
```


另一方面，如果形参是某种类型的指针或引用，则通过区分其指向的是常量对象还是非常量对象可以实现函数重载，此时的const是底层的。

例2: 编译器可以根据实参是否是const调用哪个函数。

- 因为const不能转为其他类型(P144)，所以我们只能把const对象传递给const形参。
- 当传递非常量对象或 指向非常量对象的指针时，编译器会优先选用非常量版本的函数。

```
#include<iostream>
using namespace std;

// 如果参数是指针或引用，则通过区分其指向的是常量还是非常量对象，可以实现函数重载
int lookup(int&);  //输入int的引用
int lookup(const int&); //新函数，作用于常量引用

int lookup(int *); //作用于指向int的指针
int lookup(const int *); //作用于指向 const int 的指针

int arr[]={10,11,12,30,14,50};

int main(){
    int a1=12, &r1=a1, *p1=&a1;
    int i1=lookup(r1);
    cout << "1 index of " << r1 << " is " << i1 << endl;

    const int &r2=a1;
    int i2=lookup(r2);
    cout << "2 index of " << r2 << " is " << i2 << endl;

    int i3=lookup(p1);
    cout << "3 index of " << *p1 << " is " << i3 << endl;

    const int *p2=&a1;
    int i4=lookup(p2);
    cout << "4 index of " << *p2 << " is " << i4 << endl;

    return 0;
}

int lookup(int &r){
    return -11;
}

int lookup(const int &r){
    return -12;
}


int lookup(int *p){
    for(int i=0; i<6; i++){
        if(arr[i]==*p)
            return i;
    }
    return -1;
}

int lookup(const int *p){
    return -14;
}


$ g++ d2_overload_const2.cpp 
$ ./a.out 
1 index of 12 is -11
2 index of 12 is -12
3 index of 12 is 2
4 index of 12 is -14
```


> 建议：何时不应该重载函数？

- 函数重载减轻了我们起函数名字、记名字的负担，但是应该克制使用，只在确实相似的操作上使用。
- 有些情况下，给函数起不同的名字更方便理解。

例：几个负责移动光标的函数。

```
Screen& moveHome();
Screen& moveAbs(int, int);
Screen& moveRel(int, int, string direction);
```

上述函数如果都起名叫move，则丢失了很多名字带来的信息。尽管这些函数都是在移动光标，但是移动的方式却不同。

```
//移动光标到Home位置
myScreen.moveHome(); //这种名字更容易理解，强烈推荐。
myScreen.move();
```





#### const_cast 和 重载

> const_cast: P145;

```
//比较2个string对象的长度，返回较短的那个引用
const string & shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}
```


例: 版本1，实参是常量时，使用非常量引用接收报错。

```
#include<iostream>
using namespace std;

// 返回较短的字符串的引用
// 当实参不是const时，返回的结果仍然是const string 的引用
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}

int main(){
    string x1="hi", x2="hello";
    //string &y1=shorterString(x1, x2);// 返回的y1指向哪里?
    //error: binding reference of type ‘std::string&’ to ‘const string’
    string y1=shorterString(x1, x2); // 相当于复制

    const string &y2=shorterString(x1, x2); //返回的是引用，y2地址和x1一致：
    cout << "&x1=" << &x1 << endl;
    cout << "&y1=" << &y1 << endl; // 地址和x1不同
    cout << "&y2=" << &y2 << endl;

    y1="Hi"; //修改y1不影响原x1的值
    cout << "x1=" << x1 << endl;
    //y2="Hi"; // error: passing ‘const string’ 错误，不能使用const引用修改原值

    return 0;
}


$ g++ d3_const_cast_overload.cpp 
$ ./a.out 
&x1=0x7ffed67f1d80
&y1=0x7ffed67f1dc0
&y2=0x7ffed67f1d80
x1=hi
```


例2: 版本2，实参是常量时，使用非常量引用接收正常。

- 先把实参强转为对 const 的引用，然后调用 shorterString 函数的 const 版本。
- const 版本返回对 const string 的引用，这个引用事实上绑定在某个非常量实参上。再强转去掉const，转换为普通 string&，这显然是安全的。 

```
#include<iostream>
using namespace std;

// 返回较短的字符串的引用
// 当实参不是const时，返回的结果仍然是const string 的引用
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}

//重构一个：当实参不是常量时，得到的结果也是一个普通的引用
string &shorterString(string &s1, string &s2){
    auto &r=shorterString( const_cast<const string&>(s1), 
                           const_cast<const string&>(s2) );
    return const_cast<string&>(r);
}

int main(){
    string x1="hi", x2="hello";

    //2. 当输入不是常量时，返回的也不是常量
    string &y1=shorterString(x1, x2); //只有第一个函数时报错，加重载函数后就对了
    cout << y1 << endl;

    //查看地址
    cout << "&x1: " << &x1 << endl;
    cout << "&y1: " << &y1 << endl;

    //那就可以修改值
    y1="Hi!";
    cout << x1 << endl;

    return 0;
}



$ g++ d3_const_cast_overload2.cpp 
$ ./a.out 
hi
&x1: 0x7ffe8083c400
&y1: 0x7ffe8083c400
Hi!
```




#### 调用重载的函数

- 根据实参调用一组重载函数中的某个。 
- 函数匹配 (function matching) 是值一个过程：把函数调用和一组重载函数中某一个关联起来，函数匹配的过程也叫做 重载确定(overload resolution)。
    * 编译器把实参与重载集合中的每一个函数的形参进行比较，确定调用哪一个函数。


- 参数数量不同、或类型不同，一般很容易确定。
- 但是当参数类型可以互相转换(P141)时，就比较麻烦了。P217：编译器怎么处理存在类型转换的函数调用的。


当调用重载时有三种可能的结果:

- 编译器找到一个与实参 最佳匹配(best match) 的函数，并调用该函数的代码
- 找不到，编译器发出无匹配(no match)的错误信息
- 多于一个可以匹配，都不是最佳匹配，此时报错，称为 二义性调用(ambiguous call)







### 重载与作用域

- 内层中声明名字，将隐藏外层同名实体。不同作用域无法重载函数名。

```
#include<iostream>
using namespace std;


//不同作用域无法重载函数

string read();
void print(const string &);
void print(double); //重载 print 函数

void fooBar(int ival){
    bool read=false; //内层作用域：隐藏了外层的read
    //string s=read(); //错误：read是一个布尔值，不是函数
    //error: ‘read’ cannot be used as a function

    //不好的习惯：在局部作用域声明函数
    void print(int); //新作用域：隐藏了之前的print，如果不声明，则最后一个 print(3.4) 输出 3.4；声明后则输出3

    //print("Value: "); //错误，外部的 print(const string &); 被隐藏掉了
    //error: invalid conversion from ‘const char*’ to ‘int’


    print(ival); //ok: 当前作用域 print(int) 可见
    print(3.14); //ok: 调用 print(int)，外部的 print(double) 被隐藏了
}

int main(){
    fooBar(5);
    return 0;
}


// 不能在函数内定义函数，不允许函数嵌套
// https://cplusplus.com/forum/beginner/199701/
void print(int x){
    cout << "int " << x << endl; 
}

void print(const string &x){
    cout << "const string &x=" << x << endl; 
}

void print(double x){
    cout << "double x=" << x << endl; 
}

$ g++ d4_overload_scope.cpp 
$ ./a.out 
int 5
int 3
```

> 在C++中，名字查找发生在类型检查之前。

一旦在当前作用域中找到所需的名字，编译器就会忽略掉外层作用域中的同名实体。剩下的工作就是检查函数调用是否有效了。












## 6.5 特殊用途的语言特性


三种函数相关的语言特性： 默认实参、内联函数、constexpr函数，以及程序调试过程中常用的一些功能。


### 默认实参 (default argument)

- 就是可以在定义时给参数默认值。调用时可以省略该参数，从而使用默认值。
- 定义时一旦一个参数有默认值，它后面的形参都必须有默认值。
- 调用时，只能省略尾部的若干有默认值的参数。

```
// 定义
typedef string::size_type sz; //typedef 参见 2.5.1 P60
string screen(sz ht=24, sz wid=80, char background=' ');

//调用
string window;
window = screen();             // 等价于  screen(24, 80, ' ')
window = screen(66);           // 等价于  screen(66, 80, ' ')
window = screen(66, 256);      // 等价于  screen(66, 256, ' ')
window = screen(66, 256, '#'); // 等价于  screen(66, 256, '#')

window=screen(,, '?'); //错误：只能省略尾部的实参
window=screen('?'); //调用 screen('?', 80, ' ') 
// 最后一个虽不报错，但是不是想要的结果。'?' 对应十进制的63，所以把63传递给形参 height
```


设计参数列表时，把不怎么使用默认值的放前面，经常使用默认值的放后面。

```
#include<iostream>
using namespace std;

// 默认实参
int increase(int x, int delta=1){
    return x+delta;
}

int main(){
    //调用
    int a=10;
    cout << increase(a) << endl;
    cout << increase(a, 1) << endl;
    cout << increase(a, 15) << endl;

    return 0;
}

$ g++ d5_default_argument.cpp 
$ ./a.out 
11
11
25
```



#### 默认实参声明

通常把函数声明放到头文件中，而且一个函数只声明一次，但多次声明同一个函数也是合法的。

> 注意：给定的作用域中，一个形参只能赋予一次默认实参。

- 也就是说后续的函数声明只能为没有默认值的形参添加默认实参
- 而且右侧的所有形参都必须有默认值。

```
// 表示高度和宽度的没有默认值
string screen(sz, sz, char=' ');
string screen(sz, sz, char='#'); //错误：重复声明。不能修改已有的默认实参
string screen(sz=24, sz=80, char); //正确：添加默认实参
```

> 通常，在函数声明中指定默认实参，并将该声明放在合适的头文件中。


```
#include<iostream>
using namespace std;

//默认实参只能声明一次
int add(int, int, int z=10); //最后一个有默认实参
// 形参的名字无关紧要
int add(int, int y2=20, int ); //再次声明时，为没有默认值的提供默认值
// 甚至不要形参名字，默认值只给类型
int add(int = -12, int y3, int );

int main(){
    cout << add() << endl; //不要参数，全部使用默认值
    cout << add(1) << endl;
    cout << add(1, 100) << endl;
    cout << add(1, 100, 300) << endl;
    //cout << add(1, z=100) << endl; //error: ‘z was not declared in this scope

    return 0;
}

//函数实现时，可以不管其他值
int add(int x, int y, int z){
    return x+y+z;
}

$ g++ d6_default_argument_decl.cpp 
$ ./a.out 
18
31
111
401
```




#### 默认实参初始值

局部变量不能作为默认实参。除此之外，只要表达式的类型能转为形参所需的类型，该表达式就能作为默认实参。

```
// wd/def/ht的声明必须出现在函数之外
sz wd=80;
char def=' ';
sz ht();

string screen(sz=ht(), sz=wd, char=def);
string window = screen(); //调用 screen(ht(), 80, ' ');
```

用作默认实参的名字在函数声明所在的作用域内解析，而这些名字的求值过程发生在函数调用时。

```
void f2(){
    def='*';  //改变默认值
    sz wd=100; //隐藏了外层定义的wd，但是没有改变默认值
    window = screen(); //调用 screen(ht(), 80, '*');
}
```

- 在函数 f2() 内，改变 def 的默认值，则对screen 的调用将会传递这个更新过的值。
- 另一方面，我们声明了一个局部变量用于隐藏外层的wd，但是该局部变量与传递给screen的默认实参没有任何关系。

//todo 细微差异，重点


例: 我的理解，解析就是绑定到某个实参的地址，求值，就是在调用的环境中按地址求值。

```
#include<iostream>
using namespace std;

// 默认实参是变量时，绑定是函数声明所在的环境，求值是函数调用所在的环境

//函数声明
int width=80;
int height=200;
char ch='#';
void screen(int w=width, int h=height, char ch=ch){
    cout << ">> w=" << w << ", h=" << h << ", ch=" << ch << endl;
}

void fn(){
    screen();
    //修改调用环境
    width=8; //更新了外部变量width
    int height=5; // 隐藏了外部变量，这个内部变量与screen函数默认实参没有关系了。
    //height=500; //看声明和定义谁先出现，
    //如果对height赋值先出现，则认为是外部变量；如果声明先出现，认为是局部新变量。

    screen();
}

int main(){
    fn();
    return 0;
}


$ g++ d7_default_argument_bind_eval.cpp 
$ ./a.out 
>> w=80, h=200, ch=#
>> w=8, h=200, ch=#
```




### 内联函数与 constexpr 函数

把一些短小的操作定义成函数，有很多优点：

- 容易阅读和理解
- 不容易出错
- 方便查找和修改
- 代码复用

缺点: 函数调用是有额外开销的。


#### 内联函数可以避免函数调用的开销

比较理想的选择是：
- 在函数的返回类型前加上 `inline` 关键字即可将函数定义为内联函数(inline);
- 调用内联函数: `cout << shorterString(s1, s2) << endl;`
- 编译时会展开成如下形式: `cout << (s1.size() < s2.size() ? s1 : s2) << endl;`
- 从而消除了运行函数 shorterString 时的开销。

> 内联说明只是向编译器发出的请求，编译器可以忽略这个请求。


```
#include<iostream>
using namespace std;

// 内联函数
inline const string &
shorterString(const string &s1, const string &s2){
    return s1.size() < s2.size() ? s1 : s2;
}

int main(){
    string x1="hi", x2="hello";
    cout << shorterString(x1, x2) << endl;

    return 0;
}

$ g++ d8_inline.cpp 
$ ./a.out 
hi
```

- 内联函数适合优化规模小、流程直接、频繁使用的函数。很多编译器不支持内联递归函数，而且一个75行的大函数也不太可能在调用点内联的展开。


例: 怎么证明是否内敛的展开了？ //todo 暂时不会 A1/6/d9_inline2.cpp 





#### constexpr 函数

是能用于常量表达式(P58, 2.4.4)的函数。

函数的返回类型和所有形参都是字面值类型，而且函数体中必须有且只有一条return 语句:

```
constexpr int new_sz() { return 52;}
constexpr int foo=new_sz(); //正确，foo是一个常量表达式
```

- 定义成无参数的形式。
- constexpr 函数被隐式的定义为内联函数。
- constexpr 函数内也可以包含其他语句，只要这些语句在运行时不执行任何操作即可。例如：空语句、类型别名、using声明。

例: 也可以是有参数形式，并返回一个非常量

```
// 如果 arg 是常量表达式，则 scale(arg) 也是常量表达式
constexpr size_t scale(size_t cnt){ return new_sz() * cnt;}
```

> 当函数的实参是常量表达式时，它的返回值也是常量表达式；反之则不然。

```
int arr[scale(2)]; //正确，scale(2) 是常量表达式。编译器用返回结果替换对scale 函数的调用
int i=2; //i不是常量表达式
int a2[scale(i)]; //错误：scale(i) 不是常量表达式
```

> constexpr 函数不一定返回常量表达式。




#### 把内联函数和 constexpr 函数放在头文件中


- 和其他函数不同，内联函数和 constexpr 函数可以在程序中多次定义。不过，多个定义必须完全一致。
- 所以，这2类函数通常定义在头文件中







### 6.5.3 调试帮助

类似头文件保护的技术(P67, 2.6.3)

- 程序可以包含一些用于调试的代码，这些代码只在开发程序时使用。
- 当准备发布时，先屏蔽掉这些代码。
- 用到两项预处理功能: assert 和 NDEBUG


#### assert 预处理宏

预处理宏的行为，类似于内联函数。

- assert 宏使用一个表达式作为它的条件: `assert(expr);`
- 首先对expr 求值，如果是假(0)，assert 输出信息并终止程序的执行。如果为真(非0)，则assert什么也不做。


- assert 宏定义在 cassert 头文件中。
- 预处理名字由预处理器管理而不是编译器，所以不用提供using声明。也就是说使用 assert 而不是 std::assert。
- 和预处理变量一样，宏名字在程序中必须唯一。
- 一般地，不要使用 assert 作为变量、函数或者其他实体的名字，防止其他程序或库使用该名字，即使你没有引入 cassert 库。


用途: assert 宏常用于检查“不能发生”的条件。比如单词长度必须大于某个阈值: `assert(word.size() > threshold);`

```
#include<iostream>
#include<cassert>
using namespace std;

//assert 常用语检查不能发生的条件
double divide(int x, int y){
    assert(y!=0);
    cout << ">> this line after asssert;" << endl;
    return static_cast<double>(x) /y;
}

int main(){
    cout << divide(10,3) << endl;
    cout << divide(10,0) << endl;

    return 0;
}

$ g++ d10_assert.cpp 
$ ./a.out 
>> this line after asssert;
3.33333
a.out: d10_assert.cpp:7: double divide(int, int): Assertion `y!=0' failed. #直接报错，不再执行 assert 后的语句
Aborted (core dumped)
```





#### NDEBUG 预处理变量

assert 的行为依赖于一个名叫 NDEBUG 的预处理器的状态。

- 如果定义了 NDEBUG，则assert 什么也不做。默认没有定义 NDEBUG，此时，assert 执行运行时检查。
- 可以使用 `#define NDEBUG` 关闭调试状态；
- 也可以从编译命令上定义预处理变量 `g++ -D NDEBUG main.c`, 相当于在main.c文件的一开始写了 `#define NDEBUG`


因为正式版时 assert 都是失效的，所以 assert 应该仅限于验证那些确实不可能发生的事情。

- assert 当做一种调试辅助手段，而不能替代真正的运行时逻辑检查，也不能替代程序本身应该包含的错误检查。

```
$ g++ -D NDEBUG d10_assert.cpp #使用 -D NDEBUG 编译，使 assert 失效

$ ./a.out 
>> this line after asssert;
3.33333
>> this line after asssert;
inf
```


- 除了用于assert之外，还可以使用 NDEBUG编写自己的条件调试代码。
    * 如果NDEBUG未定义，将执行 #ifndef 和 #endif 之间的语句；
    * 如果定义了 NDEBUG，这些代码将忽略掉

```
#include<iostream>
using namespace std;

//#define NDEBUG 使用这句定义，或者编译时参数 -D NDEBUG，都能使 #ifndef #endif之间的语句失效

// NDEBUG 编写调试语句
void print(const int ia[], size_t size){
    #ifndef NDEBUG
      // __func__ 是编译器定义的一个局部静态变量，用于存放函数的名字
      cerr << __func__ << ": array size is " << size << endl;
    #endif
    cout << "from func: " << __func__ << endl;
}

int main(){
    int arr[]={0,1,2,3}, size=sizeof(arr)/sizeof(int);
    print(arr, size);
    return 0;
}


$ g++ d11_NDEBUG.cpp 
$ ./a.out 
print: array size is 4  #多了这一行
from func: print

$ g++ -D NDEBUG d11_NDEBUG.cpp  #定义NDEBUG后就没了
$ ./a.out 
from func: print
```

> 变量 `__func__` 输出当前调试的函数名字。编译器为每个函数都定义了 `__func__`，它是 const char 的一个静态数组，用于存放函数的名字。

- C++编译器还定义了另外4个对于程序调试很有用的名字：
    * `__FILE__` 存放文件名的字符串字面量
    * `__LINE__` 存放当前行号的整数型字面值
    * `__TIME__` 存放文件编译时间的字符串字面值
    * `__DATE__` 存放文件编译日期的字符串字面值
- 可以将这些常量在错误消息中提供更多信息

```
#include<iostream>
using namespace std;

// 构建错误信息，使用编译器定义的字符串
bool checkLength(string word, int threshold){
    if(word.size() < threshold){
        cerr << "Error: " << __FILE__ << ": in function " << __func__ 
             << " at line " << __LINE__ << endl //竟然可以换行且继续输出
             << "     Compiled on " << __DATE__ << " at " << __TIME__ << endl 
             << "     Word read was \"" << word
             << "\": Length too short" << endl;
        return false;
    }
    return true;
}

int main(){
    string s2="hi";
    bool rs=checkLength(s2, 5);
    cout << (rs? "ok":"not ok") << endl;

    return 0;
}


$ g++ d12_err_message_DIY.cpp 
$ ./a.out 
Error: d12_err_message_DIY.cpp: in function checkLength at line 8
     Compiled on Aug 12 2022 at 10:38:13
     Word read was "hi": Length too short
not ok
```









## 6.6 函数匹配

重载函数怎么匹配？


```
void f();
void f(int);
void f(int, int);
void f(double, double=3.14);
f(5.6); 调用 void f(double, double)
```

#### 确定候选函数和可行函数

- 首先确定 候选函数 candidate function，具备2个条件: 与被调函数同名，且其声明在调用点可见。
- 第二步考察提供的实参，从候选函数中选出能被这组实参调用的函数，被选出的叫 可行函数(viable function)。具备2个条件：实参数量相等，类型对应或能转换成形参类型。
    * 如果函数定义的有默认实参，则传入的实参个数可以少于它实际使用的实参数量。
- 如果没有找到可行函数，则编译器报错：无匹配函数。


#### 寻找最佳匹配(如果有的话)

实参和形参的类型越接近，匹配的越好。

精确匹配比需要类型转换的匹配效果好。


#### 含有多个形参的函数匹配

`f(42, 2.56);` 怎么匹配呢？

- 可行函数 f(int, int) 和 f(double, double)。
- 如果有且只有一个函数满足下列条件，则匹配成功：
    * 该函数的每个实参的匹配都不劣于其他可行函数需要的匹配
    * 至少一个实参的匹配优于其他可行函数提供的匹配
- 如果没有一个函数脱颖而出，则该调用是错误的。编译器将报错：二义性调用。


解析:

- 只考虑第一个参数，f(int, int) 优于 f(double, double);
- 只考虑第二个参数，则 f(double, double) 优于 f(int, int).
- 编译器会报错：二义性。整体无法判定孰优孰劣。


```
#include<iostream>
using namespace std;

//二义性调用
void f();
void f(int);
void f(int, int);
void f(double, double=3.14);

int main(){
    f(12, 2.5); //error: call of overloaded ‘f(int, double) is ambiguous
    return 0;
}

void f(int, int){
    cout << "int" << endl;
}
void f(double, double){
    cout << "double" << endl;
}

$ g++ d13_ambiguous.cpp #编译报错：二义性。报错信息见代码注释
```

> 调用重载函数时应尽量避免强制类型转换。如果实际中确实需要强转，说明设计的形参集合不合理。






### 6.6.1 实参类型转换

编译器将实参类型转换到形参类型分了几个等级：

1. 精确匹配，包括:
    - 实参类型和形参类型相同
    - 实参从数组类型或函数类型转换成对应的指针类型(P221, 6.7 函数指针)
    - 向实参添加顶层const或者从实参中删除顶层const
2. 通过const转换实现的匹配(P143, 4.11.2)
3. 通过类型提升实现的匹配(P142, 4.11.1)
4. 通过算术类型转换(P142, 4.11.1) 或指针转换(P143, 4.11.2) 实现的匹配
5. 通过类类型转换实现的匹配(P514, 14.9)



#### 需要类型提升和算术类型转换的匹配

> 警告: 内置类型的提升和转换可能在函数匹配时产生意想不到的结果。设计良好的话，本例的形参很少出现。

```
void ff(int);
void ff(short);
ff('a'); //char 提升为 int；调用 ff(int)
```

所有算术类型转换的级别都一样: int 到 unsigned int 的转换 并不比 int 到 double 的转换级别高。

```
void f2(long);
void f2(float);
f2(3.14); //错误：二义性调用
```

字面量 3.14 是double类型，它能转换成 long 或 float。因为存在两种可能的算术类型转换，所以调用具有二义性。

```
#include<iostream>
using namespace std;

//二义性调用
void f2(long){};
void f2(float){};


int main(){
    f2(3.14); //error: call of overloaded ‘f2(double) is ambiguous
    return 0;
}

$ g++ d13_ambiguous2.cpp
```




#### 函数匹配和 const 实参

如果重载函数的区别在于

- 他们的引用类型的形参是否引用了 const
- 或指针类型的形参是否指向 const

则调用发生时编译器根据实参是否常量类决定选择哪个函数。

```
void f3(int &); //函数的参数是 int 的引用
void f3(const int &); //函数的参数是一个常量引用
const int a=10;
int b=20;

f3(a); //调用 f3(const int &)
f3(b); //调用 f3(int &)
```

- 第一个传入的是 const 类型实参，因为不能把普通变量绑定到 const 对象上，所以唯一可行的函数是常量引用作为形参的哪个函数。且该函数与实参精确匹配。
- 第二个传入的是 非常量对象，则两个都是可行函数。而需要类型转换的就不算精确匹配。所以优先选用非常量版本的函数。


例: 形参是常量引用和非常量引用。

```
#include<iostream>
using namespace std;

//形参有const的引用或指针
void f3(int &){ cout << "int &" << endl;} //函数的参数是 int 的引用
void f3(const int &){ cout << "const int &" << endl;} //函数的参数是一个常量引用
const int a=10;
int b=20;

int main(){
    f3(a); //调用 f3(const int &)
    f3(b); //调用 f3(int &)

    return 0;
}

$ g++ d14_para_const.cpp 
$ ./a.out 
const int &
int &
```

例2: 形参是常量指针和非常量指针。

```
#include<iostream>
using namespace std;

//形参有const的常量或指针
void f4(int *){ cout << "int *" << endl;} //函数的参数是指向 int 的指针
void f4(const int *){ cout << "const int *" << endl;} //函数的参数是一个指向 常量int 的指针

int a=10, b=20;
const int *pa=&a;
int *pb=&b;

int main(){
    f4(pa); //调用 f4(const int *)
    f4(pb); //调用 f4(int *)

    return 0;
}

$ g++ d15_para_const_ptr.cpp 
$ ./a.out 
const int *
int *
```

- 实参是指向常量的指针，调用形参是 const int* 的函数；
- 实参是指向非常量的指针，调用形参是普通指针的函数。










## 6.7 函数指针

函数指针，是一个指针，指向的是函数。

- 函数指针指向某种特定类型。
- 函数的类型由它的返回类型和形参类型共同决定，与函数名无关。

```
// 比较2个string对象的长度
bool lengthCompare(const string &, const string &);
```

该函数的类型是 bool(const string&, const string &)。使用指针替换函数名，就声明了一个指向该函数的指针：

```
// pf指向一个函数，该函数的返回值是 bool 类型，形参是 2个 const string 的引用
bool (*pf)(const string &, const string &); //未初始化
```

按结合性，从内向外分析:

- (*pf) 表示pf是一个指针；
- 右侧是形参列表，表示pf指向的是函数；
- 左侧，函数的返回值是布尔值。

> 注意: *pf 两端的圆括号不能省略。否则，pf2就是一个返回值为bool指针的函数: 

```
// 声明 pf2 为函数，返回值为 bool *
bool *pf2(const string&, const string &);
```


#### 使用函数指针

当我们把函数名作为一个值使用时，该函数自动转换成指针。

把函数 lengthCompare 的地址赋值给pf:

```
pf = lengthCompare;  //pf 指向名为 lengthCompare 的函数
pf2= &lengthCompare; //等价的赋值语句: 取地址符是可选的
```

可以直接使用指向函数的指针调用该函数，解引用是可选的:

```
bool b1=lengthCompare("hi", "hello"); //直接使用函数名
bool b2= (*pf)("hi", "hello"); //解引用
bool b3= pf("hi", "hello"); //不解引用，也可以
```

例1:

```
#include<iostream>
using namespace std;

//获取函数的指针
// 比较2个string对象的长度
bool lengthCompare(const string &s1, const string &s2){
    return s1.size() > s2.size();
}

// pf指向一个函数，该函数的返回值是 bool 类型，形参是 2个 const string 的引用
bool (*pf)(const string &, const string &); //未初始化
bool (*pf2)(const string &, const string &) = &lengthCompare; //初始化

int main(){
    cout << (void *)lengthCompare << endl;
    pf = lengthCompare;
    //pf2= &lengthCompare; //取地址符是可选的
    cout << (void *)pf << endl;
    cout << (void *)pf2 << endl;

    //2. 使用函数指针，无需提前解引用
    bool b1=lengthCompare("hi", "hello"); //直接使用函数名
    bool b2= (*pf)("hi", "hello"); //解引用
    bool b3= pf("hi", "hello"); //不解引用，也可以
    cout << "b1=" << b1 << endl;
    cout << "b2=" << b2 << endl;
    cout << "b3=" << b3 << endl;

    return 0;
}

$ g++ e1_fun_ptr1.cpp 
$ ./a.out 
0x55d0990462c9
0x55d0990462c9
0x55d0990462c9
b1=0
b2=0
b3=0
```



- 指向不同函数类型的指针之间不存在转换规则。
- 我们可以为函数指针赋值 nullptr(P48, 2.3.2)，或者值为0的整型常量表达式，表示该指针没有指向任何一个函数。

```
string::size_type sumLength(const string&, const string&);
bool cstringCompare(const char*, const char*);
pf=0; //正确：pf不指向任何函数
pf=sumLength; //错误：返回类型不匹配

pf=cstringCompare; //错误：形参类型不匹配
pf=lengthCompare; //正确：函数和指针的类型精确匹配
```

例2: 指针类型和函数的匹配，看形参列表和返回值。

```
#include<iostream>
using namespace std;

//函数指针，只识别形参和返回值，不识别函数名

bool lengthCompare(const string &s1, const string &s2){
    cout << __func__ << endl;
    return s1.size() > s2.size();
}

bool cmpFirstString(const string &s1, const string &s2){
    cout << __func__ << endl;
    return s1[0] > s2[0];
}

int totalSize(const string &s1, const string &s2){
    return s1.size() + s2.size();
}

bool (*pf)(const string&, const string &);

int main(){
    string x="hello", y="Anderson";
    pf=lengthCompare;
    cout << pf(x, y) << endl;

    pf=&cmpFirstString;
    cout << pf(x, y) << endl;

    //pf=totalSize; 
    //error: invalid conversion from ‘int (*)(const string&, const string&)’ to ‘bool (*)(const string&, const string&)’

    return 0;
}

$ g++ e2_fun_ptr.cpp 
wangjl@YStation:~/data/project/learnCpp/A1/6$ ./a.out 
lengthCompare
0
cmpFirstString
1
```



#### 重载函数的指针

如果定义了重载函数，

```
void ff(int *);
void ff(double);

void (*pf1)(double) = ff; //pf1指向 ff(double);
```

编译器通过指针类型决定选用哪个函数，指针类型必须和重载函数中的某一个精确匹配。

```
void (*pf2)(int)=ff; //错误：没有一个ff与该形参列表精确匹配
string (*pf3)(int *)=ff; //错误: ff和pf3的返回类型不匹配
```



#### 函数指针形参

- 和数组类似(P193, 6.2.4)，虽然不能定义函数类型的形参，但是形参可以是指向函数的指针。
- 此时，形参看起来是函数类型，实际上却是当成指针使用

```
// 第三个形参是函数类型，他会自动转换成指向函数的指针
void useBigger(const string &s1, const sting &s2, 
    void pf(const string&, const string&));

//等价的声明：显式的将形参定义成指向函数的指针
void useBigger(const string &s1, const sting &s2, 
    void (*pf)(const string&, const string&));
```

可以直接把函数作为实参使用，此时它会自动转换成指针：

```
// 自动将函数 lengthCompare 转换成指向该函数的指针
useBigger(s1, s2, lengthCompare);
```

例: 函数指针作为参数。

```
#include<iostream>
using namespace std;

//函数指针可以作为参数

bool lengthCompare(const string &s1, const string &s2){
    return s1.size() > s2.size();
}

bool lengthCompare2(const string &s1, const string &s2){
    return s1.size() < s2.size(); //和上一个相反
}

const string &useBigger(const string &s1, const string &s2, 
    bool (*pf)(const string&, const string&)){
        return ( pf(s1, s2) ? s1 : s2 );
}

int main(){
    string s1="hi", s2="hello";

    //获取长的字符串
    const string &x1=useBigger(s1, s2, lengthCompare);
    cout << x1 << endl;
    cout << &x1 << "\t" << &s2 << endl;

    // 换一个比较函数
    cout << useBigger(s1, s2, &lengthCompare2) << endl; //加&fn 是可选的

    return 0;
}

$ g++ e3_fun_ptr_as_parameter.cpp 
$ ./a.out 
hello
0x7fffd9874ba0  0x7fffd9874ba0
hi
```




直接使用函数指针类型显得冗长而繁琐。类型别名(P60, 2.5.1) 和 decltype(P62, 2.5.3) 能让我们简化使用函数指针的代码:

```
//Func 和 Func2 是函数类型
typedef bool Func(const string&, const string&); //形式1
typedef decltype(lengthCompare) Func2; //等价形式

// FuncP 和 FuncP2 是指向函数的指针
typedef bool (*FuncP)(const string&, const string&);
typedef decltype(lengthCompare) *FuncP2; //等价的类型
```

需要注意，decltype 返回函数类型，不会讲函数类型自动转换成指针类型。所以需要在前面加上*才能得到指针。

```
//useBigger 的等价声明，其中使用了类型别名
void useBigger(const string&, const string&, Func); //编译器将函数名自动转为指针
void useBigger(const string&, const string&, FuncP2); //直接传入指针
```


例: 函数指针作为参数，简化写法

```
#include<iostream>
using namespace std;

//函数指针可以作为参数，简化写法

bool lengthCompare(const string &s1, const string &s2){
    return s1.size() > s2.size();
}

bool lengthCompare2(const string &s1, const string &s2){
    return s1.size() < s2.size(); //和上一个相反
}

//简化函数指针的写法
typedef bool (*FunP)(const string&, const string&); //声明1
typedef decltype(lengthCompare) *FuncP2; //声明2

const string &useBigger(const string &s1, const string &s2, 
    FuncP2 pf){ //最后一个参数简化了
        return ( pf(s1, s2) ? s1 : s2 );
}

int main(){ //main函数没变
    string s1="hi,", s2="hello";

    // 获取长字符串
    cout << useBigger(s1, s2, lengthCompare) << endl;

    // 换一个比较函数: 获取短字符串
    cout << useBigger(s1, s2, &lengthCompare2) << endl; //加&fn 是可选的

    return 0;
}

$ g++ e4_fun_ptr_as_parameter_Sim.cpp 
$ ./a.out 
hello
hi,
```











#### 指向返回函数的指针

- 和数组类似，函数不能返回函数，但是可以返回指向函数的指针。
- 必须把返回类型写成指针形式。
- 最简单的方式是使用类型别名

```
using F=int(int*, int); //F是函数类型，不是指针
using pF=int(*)(int*, int); //pF是指针类型
```

其中我们使用类型别名(P60, 2.5.1) 将F定义成函数类型，将pF定义成指向函数的指针。

> 和函数类型的形参不同，返回类型不会自动的转换成指针。必须显式的将返回类型指定为指针。

```
pF f1(int); //正确: pF是指向函数的指针，f1返回指向函数的指针
F f1(int); //错误：F是函数类型，f1不能返回一个函数
F *f1(int); //正确: 显式的指定返回类型是指向函数的指针
```

当然，我们也可以直接声明f1: `int (*f1(int))(int*, int);` 按结合性从内向外拆解理解:

- f1(int) 说明f1是有形参列表的，f1是一个函数；
- (*f1(int)) 前面加星号，说明返回一个指针；
- 再看右侧，指针本身也包含形参列表，因此指针指向一个函数
- 再看左侧，该函数的返回值是int


还可以使用尾置返回类型的方式(P206, 6.3.3)，声明一个返回函数指针的函数: `auto f1(int) -> int(*)(int*, int);`


例: 返回函数指针的函数，三种声明方式。

```
#include<iostream>
using namespace std;

//返回函数指针的函数：依据输入int的正负，返回一个指针，指向以下2个函数中的一个

int getMax(int *p1, int *p2){
    return *p1>*p2 ? *p1 : *p2;
}

int getMin(int *p1, int *p2){
    return *p1<*p2 ? *p1 : *p2;
}


//method1 直接声明: 最难理解的形式
int (*pf1(int n))(int*, int*){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}
/*
从内到外拆开理解
* 最核心的 pf1(int n) 说明是一个函数，形参列表是 int n
* 前面有星号，表示其返回值是一个指针
* 看右侧：指向的函数的形参列表(int*, int*)
* 看左侧：指向的函数的返回值是 int
*/

//method2: 使用类型别名
using Fun = int(int*, int*); //函数类型
using pFun = int(*)(int*, int*); //指向函数的指针

Fun *pf2(int n){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}

pFun pf2_(int n){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}

//C风格的类型别名
typedef int Fun2(int*, int*); //使用 typedef，函数类型
typedef int (*pFun2)(int*, int*); //使用 typedef，函数类型，函数指针
pFun2 pf2_2(int n){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}


//medthod3: 尾置返回类型
auto pf3(int n) -> int(*)(int *, int*){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}

int main(){
    int i=-2, j=500;
    // test1
    cout << ">> method1" << endl;
    cout << pf1(1)(&i, &j) << endl;
    cout << pf1(-5)(&i, &j) << endl;
    // test2
    cout << ">> method2" << endl;
    cout << pf2(1)(&i, &j) << endl;
    cout << pf2(-5)(&i, &j) << endl;

    cout << pf2_(1)(&i, &j) << endl;
    cout << pf2_(-5)(&i, &j) << endl;
    
    cout << pf2_2(1)(&i, &j) << endl;
    cout << pf2_2(-5)(&i, &j) << endl;
    // test3
    cout << ">> method3" << endl;
    cout << pf3(1)(&i, &j) << endl;
    cout << pf3(-5)(&i, &j) << endl;

    return 0;
}

$ g++ e5_return_fun_ptr.cpp 
$ ./a.out 
>> method1
500
-2
>> method2
500
-2
500
-2
500
-2
>> method3
500
-2
```



#### 将 auto 和 decltype 用于函数指针类型

如果明确知道返回类型是哪一个，就可以使用 decltype 简化书写函数指针返回类型的过程。

我们有2个函数，参数和返回类型相同。第三个函数接受一个string 参数，返回一个指针，指向前2个函数中的一个。

```
string::size_type sumLength(const string&, const string&);
string::size_type largerLength(const string&, const string&);

//根据其形参的取值，getFcn函数返回指向 sumLength 或 largerLength 的指针
decltype(largerLength) *getFcn(const string&);
```

声明getFcn唯一要注意的点是：牢记 decltype 作用于某个函数，返回的是函数而非指针类型。需要显式的添加*表明返回的是指针，而不是函数本身。





> 2022.8.12 done;