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














## 6.3 返回类型和return语句





























## 6.4 函数重载





























## 6.5 特殊用途的语言特性





























## 6.6 函数匹配






























## 6.7 函数指针











































