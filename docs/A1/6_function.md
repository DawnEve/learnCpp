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















## 6.4 函数重载





























## 6.5 特殊用途的语言特性





























## 6.6 函数匹配






























## 6.7 函数指针











































