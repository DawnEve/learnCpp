# 2 变量和基本类型

`$ cd mkdir A1/2/`

## 内置类型

### 类型转换

```// a1_convert.cpp
#include<iostream>
int main(){
    unsigned u=10;
    int i=-42;
    std::cout << "i+i=" << i+i << std::endl; //-84
    std::cout << "i+u=" << i+u << std::endl; //4294967264
    std::cout << "u+i=" << u+i << std::endl; //4294967264
    return 0;
}
```



### 转义序列

制作一个进度条。要点: 

- 睡眠 0.1s; 
- 不换行，移动到当前行的最前面 \r


```
$ cat a2_progression.cpp
#include<iostream>
#include<string>
#include <unistd.h>
using namespace std;

// 进度条: 原生实现

int main(){
    int total=80;
    float ratio=0;
    string row=" ";
    // 百分比数字前的空格
    for(int i=0; i<=total; i++){
        row += " ";
    }

    // 显示进度条
    for(int i=0; i<=total; i++){
        string str="";
        ratio = (1.00*i)/total * 100;
        for(int j=0; j<i; j++){
            str += "=";
        }
        //1. sleep for some us; https://www.gaojiufeng.cn/?id=301
        usleep(0.05*1e6);
        //printf("%s>>\r", str.c_str() );
        //2. 只刷新缓存不换行 https://www.likecs.com/ask-152700.html
        cout << row << (int)ratio << "%\r"; 
        cout << str << "=>\r" << std::flush; 
    }
    //换行
    cout << endl;
    return 0;
}


编译执行:
$ g++ a2_progression.cpp 
$ ./a.out 
=================================================================================>100%
```










## 变量

初始化和赋值是两个完全不同的操作。区别是啥？ //todo


### 列表初始化(4种)

有四种列表初始化的方法。包括根据 C++11 新定义的花括号初始化方法。

```
#include<iostream>
using namespace std;

int main(){
    int a1=0;
    int a2={1};
    int a3{3};
    int a4(4);

    cout << "a1=" << a1 << endl;
    cout << "a2=" << a2 << endl;
    cout << "a3=" << a3 << endl;
    cout << "a4=" << a4 << endl;

    return 0;
}


$ g++ a3_init.cpp 
$ ./a.out 
a1=0
a2=1
a3=3
a4=4
```


{} 会在转换有可能损失数据的时候报错提示：
```
#include<iostream>
using namespace std;

int main(){

    long double ld=3.14159265358;
    // 错误: 转换未执行，因为存在丢失信息的风险：小数会丢失，整数可能太大丢失
    //int a1{ld}; //narrowing conversion of ‘ld’ from ‘long double’ to ‘int’
    //int a2={ld};

    // 正确：转换执行，且丢失部分数据。
    int a3(ld);
    int a4=ld;

    //cout << "a1=" << a1 << endl;
    //cout << "a2=" << a2 << endl;
    cout << "a3=" << a3 << endl;
    cout << "a4=" << a4 << endl;

    return 0;
}
```


### 默认初始化

函数内的内置类型变量将 不被初始化。里面的值是随机的，访问将引发程序错误。


```
#include<iostream>
using namespace std;

int add(int x, int y){
    int b;
    cout << "para in function, not init: " << b << endl;
    return x+y;
}

int main(){
    int a;
    cout << a << endl; //0
    cout << add(1,5) << endl; //不确定函数内的b的值
    return 0;
}


$ g++ a3_init3.cpp

$ ./a.out 
0
para in function, not init: 32664
6

$ ./a.out 
0
para in function, not init: 32745
6
```


### 声明与定义变量

声明是为了多个文件共用变量。

只声明，则使用 extern 关键字。

而定义变量，则同时申请内存空间。

extern 如果包含了初始值，则不再是声明，而是定义。

> 变量能且只能被定义一次，但是可以多次被声明。




### 标识符 identifier

就是变量名字、函数名字等。

C++除了保留字，还为标准库保留了一些名字。

约定，不报错: 用户自定义名字不能出现两个下划线，也不能以下划线加大写字母开头。函数内定义的标识符不能下划线开头。

```
#include<iostream>

using namespace std;

//命名: 用户自定义名字不能出现两个下划线，也不能以下划线加大写字母开头。函数内定义的标识符不能下划线开头。

int __ident1=1;
int _Ident2=2;

int main(){
    int _ident3=3;

    cout << "__ident1:" << __ident1 << endl;
    cout << "_Ident2:" << _Ident2 << endl;
    cout << "_ident3 in main:" << _ident3 << endl;
    return 0;
}

$ g++ a4_identifier.cpp 
$ ./a.out 
__ident1:1
_Ident2:2
_ident3 in main:3
```


#### 变量命名规范

规范命名，能提高程序的可读性，方便交流、沟通。也方便自己以后阅读。

- 有实际意义，而不是单个字母
- 一般用小写，如 index，而不是 Index 或 INDEX
- 类名一般首字母大写 class Book, class Sales_item
- 如果多个单词合成，则要有明显区分，如 student_loan 或 studentLoan，而不是 studentloan

> C++ 关键词， P43, pdf(69/864)

> C++操作符替代名: and    and_eq   bitand    bitor   compl   not   not_eq   or_eq   xor_eq   or   xor





### 名字的作用域

怎么调用 main 函数？ 可以调用，就是结果可能不符合预期。

建议：第一次使用变量时再定义它。方便赋初始值。


- 嵌套的作用域，外面定义过的变量，里面可以再定义一次，但是不建议这么做。
- 如果使用全局作用域中的变量，则可以使用前缀 ::para_name

```
#include<iostream>
using namespace std;

int book_number=1;

int main(){

    cout << "book_number in global = " << book_number << endl;

    int book_number=100;
    cout << "book_number (in main) = " << book_number << endl;
    cout << "::book_number (in global) = " << ::book_number << endl;

    return 0;
}

$ g++ a6_scope.cpp
$ ./a.out 
book_number in global = 1
book_number (in main) = 100
::book_number (in global) = 1
```



- for 中定义变量的作用范围是什么？

```
#include<iostream>
using namespace std;

// for 中定义的变量的作用范围: 循环体所在的花括号内。

int main(){
    int sum=0;
    int i=100;
    for(int i=0; i<=5;i++){
        sum+=i;
        cout << i << "\t" << sum << endl;
    }
    cout << "outside For: " << i << "\t" << sum << endl;
    return 0;
}

$ g++ a6_scope_for.cpp 
$ ./a.out 
0       0
1       1
2       3
3       6
4       10
5       15
outside For: 100        15
```










## 复合类型 compound type

好几种，这里说 引用和指针。


### 引用 reference

d是声明的变量名，写成 &d 的形式定义引用类型。
```
int iVal=2;
int &refVal = iVal; // refVal 是指向 iVal 的，是 iVal 的另一个名字
int &refVal; //报错，引用必须被初始化
```


```
#include<iostream>

using namespace std;

int main(){
    int iVal=20;
    int &refVal=iVal; //引用类型，表示 iVal 的另一个名字
    // int &refVal2; //refVal2 declared as reference but not initialized
    int &refVal3=refVal; //refVal 和 iVal 等价，所以 refVal3 也是 iVal 的另一个名字

    cout << "   iVal=" << iVal << "| pointer=" << &iVal << endl;
    cout << " refVal=" << refVal << "| pointer=" << &refVal << endl;
    //cout << "refVal2=" << refVal2 << endl;
    cout << "refVal3=" << refVal3 << "| pointer=" << &refVal3 << endl;

    return 0;
}

$ g++ a7_ref.cpp 

可见，他们值相同，确实是指向内存中同一个地址的。
$ ./a.out 
   iVal=20| pointer=0x7ffec4caa544
 refVal=20| pointer=0x7ffec4caa544
refVal3=20| pointer=0x7ffec4caa544
```

因为引用本身不是对象，所以不能定义引用的引用。



### 指针 pointer

- 指针本身就是一个对象，占用内存空间，保存的是指向其他变量的地址，可赋值和拷贝。
- 定义指针时是可以不初始化。在块作用域中，不初始化时值不确定。

指针的声明形式 *d，其中 d 是变量名。

- 获取变量的地址，就是在变量前加 取地址符 &: &value
- 获取指针指向的值，就是在 指针前加 解引用符*: *ptr


```
#include<iostream>

using namespace std;

int main(){
    int a1=120;
    int *pd=&a1; //正确：初始值是 int 型对象的地址
    int *pd2= pd; //正确: 初始值是 指向 int 对象的指针

    //double *pi=a1; //错误：指针pi的类型与变量a1的类型不匹配
    // invalid conversion from ‘int’ to ‘double*’

    cout << "a1=" << a1 << " | addr=" << &a1 << endl;
    cout << "pd=" << pd << " | addr=" << &pd << ", val=" << *pd << endl;
    cout << "pd2=" << pd2 << " | addr=" << &pd2 << ", val=" << *pd2 << endl;
    //cout << "pi=" << pi << " | addr=" << &pi << endl;
    return 0;
}


$ g++ a8_pointer.cpp
$ ./a.out 
a1=120 | addr=0x7ffc001fed24
pd=0x7ffc001fed24 | addr=0x7ffc001fed28, val=120
pd2=0x7ffc001fed24 | addr=0x7ffc001fed30, val=120
```


#### 指针的值4种状态

指针的值(即地址)应属于下列4种状态之一：
- 指向一个对象
- 指向紧邻对象所占空间的下一个位置
- 空指针，没有指向任何对象
- 无效指针，上述情况之外的其他值。


```
#include<iostream>

using namespace std;

//全局下的指针会自动初始化，局部下的不会。
int *p1;

int main(){
    int a1 = 220;
    int *p2; //未初始化，指向的内容不确定
    cout << "addr of a1: " << &a1 << endl;
    cout << "p1=" << p1 << endl;
    cout << "p2=" << p2 << " | value=" << *p2 << endl;

    p2=&a1;
    cout << "p2=" << p2 << " | value=" << *p2 << endl;

    return 0;
}

$ g++ a8_pointer2.cpp 
$ ./a.out 
addr of a1: 0x7fffbf476d2c
p1=0
p2=0x7fffbf476e30 | value=1
p2=0x7fffbf476d2c | value=220
```


#### 解引用符号 *

```
#include<iostream>
using namespace std;

int main(){
    int val=125;
    int *pA = &val; //pA 存放的是 val 的地址，或者说 pA 是指向变量 val 的指针

    cout << "val=" << val << ", *pA=" << *pA << endl;

    //赋值
    *pA=-80; //给pA的解引用，也就是pA指向的地址赋值
    cout << "val=" << val << ", *pA=" << *pA << endl;

    return 0;
}

$ g++ a8_pointer3.cpp 
$ ./a.out 
val=125, *pA=125
val=-80, *pA=-80
```



#### 空指针 null pointer

```
#include<iostream>
using namespace std;

// 生成空指针的方法
int main(){
    int *p1=nullptr; //等价于 int *p1=0; (推荐)
    int *p2=0; //直接将p2初始化为字面量0
    //需要首先 #include cstdlib
    int *p3=NULL; //等价于 int *p3=0

    int zero=0;
    //int *p4=zero; //invalid conversion from ‘int’ to ‘int*’
    // 直接把0赋值给指针可以，但是把int变量赋值给指针不行，即使它的值是0.

    cout << "value of null pointer: p1=" << p1 << endl;
    cout << "value of null pointer: p2=" << p2 << endl;
    cout << "value of null pointer: p3=" << p3 << endl;
    // 访问空指针的值报错
    //cout << "value of null pointer: *p1=" << *p1 << endl; //Segmentation fault (core dumped)
    return 0;
}

$ g++ a9_null_pointer.cpp 
wangjl@YStation:~/data/project/learnCpp/A1/2$ ./a.out 
value of null pointer: p1=0
value of null pointer: p2=0
value of null pointer: p3=0
```

> 建议给指针初始化，不确定时可以初始化为 nullptr。


**怎么区别赋值语句改变的是 指针的值 还是 指针所指向的对象的值？**

```
#include<iostream>
using namespace std;

int main(){
    // 赋值永远改变的是等号左侧的对象
    int ival=15;
    int ival2=35;
    int *pi= &ival; //初始化指针，指向的是 ival 的地址
    cout << &pi << " is addr of pi, value of pi=" << pi << ", point to *pi=" << *pi << endl;
    
    // 谁被改变了？
    pi=&ival2; //pi的值被改变了，现在pi指向 ival2
    cout << &pi << " is addr of pi, value of pi=" << pi << ", point to *pi=" << *pi << endl;

    *pi = 750; // *pi 被改变，也就是 pi 指向的值(ival2)变了，指针变量中保存的地址没变
    cout << &pi << " is addr of pi, value of pi=" << pi << ", point to *pi=" << *pi << endl;
    cout << "ival=" << ival << ", ival2=" << ival2 << endl;

    return 0;
}

$ g++ a10_assign_value.cpp 
$ ./a.out 
0x7ffeff8f5b90 is addr of pi, value of pi=0x7ffeff8f5b88, point to *pi=15
0x7ffeff8f5b90 is addr of pi, value of pi=0x7ffeff8f5b8c, point to *pi=35
0x7ffeff8f5b90 is addr of pi, value of pi=0x7ffeff8f5b8c, point to *pi=750
ival=15, ival2=750
```



#### 指针做布尔值

- 空指针布尔值是 false，任何非空指针都是true。
- 两个指针使用 == 比较，如果两个指针存放的地址相同，它们相等。



#### void* 指针

void* 是一种特殊的指针类型，可用于存放人已对象的地址。

void* 中存放的是地址，和普通指针类似。区别是我们不清楚指针指向的对象是什么类型。


```
#include<iostream>
using namespace std;

// void* 指针，不能直接去之。
// 仅仅能比较是否相等、作为函数的输入或输出，或者赋值给另一个void*指针所指的对象。

int main(){
    double obj=3.14, *pd=&obj;
    cout << "obj=" << obj << ", &obj=" << &obj << endl;
    cout << "*pd=" << *pd << ",   pd=" << pd << endl;

    void *pv =&obj; 
    cout << "1 pv=" << pv << endl;
    //cout << "pv=" << pv << ", *pv=" << *pv << endl;
    // error: ‘void* is not a pointer-to-object type

    pv=pd;
    cout << "2 pv=" << pv << endl;

    int a1=100;
    pv=&a1;
    cout << "3 pv=" << pv << endl;

    return 0; 
}

$ g++ a11_void_point.cpp 
$ ./a.out 
obj=3.14, &obj=0x7ffdeaabf890
*pd=3.14,   pd=0x7ffdeaabf890
1 pv=0x7ffdeaabf890
2 pv=0x7ffdeaabf890
3 pv=0x7ffdeaabf88c
```








### 复合类型的声明

```
#include<iostream>
using namespace std;

int main(){
    // 注意 int* i=1, j=2; 其实 *只管到i变量。
    int *ptr=nullptr, i=1024, &ref=i;
    ptr=&i;
    cout << "   i=" << i << endl;
    cout << " ref=" << ref << endl;
    cout << "*ptr=" << *ptr << endl;
    return 0;
}

$ g++ a12_declare_compound.cpp 
$ ./a.out 
   i=1024
 ref=1024
*ptr=1024
```


#### 指向指针的指针

一个变量，里面保存的是地址，指向的是另一个指针，后者指向一个变量。

```
int ival=1024;
int *pi=&ival; //pi指向一个int型的数
int **ppi=&pi; //ppi指向一个 int型的指针
```

```
#include<iostream>
using namespace std;

int main(){
    int ival=1024;
    int *pi=&ival; //pi指向一个int型的数
    int **ppi=&pi; //ppi指向一个 int型的指针
    
    // 使用 *addr 获取该指针指向的地址的值
    cout << "&ppi=" << &ppi << ", \tppi=" << ppi 
         << ", \t*ppi=" << *ppi << ", \t**ppi=" << **ppi << endl;
    cout << "&pi=" << &pi << ", \tpi=" << pi << ", \t*pi=" << *pi << endl;
    cout << "ival=" << ival << ", \taddr=" << &ival << endl;

    // 使用 &获取地址
    cout << "\nppi=" << ppi << " ==> &pi=" << &pi << ", pi=" << pi << " ==> &ival=" << &ival << endl;
    return 0;
}


$ g++ a13_point_to_pointer.cpp 
$ ./a.out 
&ppi=0x7ffff27e6010,    ppi=0x7ffff27e6008,     *ppi=0x7ffff27e6004,    **ppi=1024
&pi=0x7ffff27e6008,     pi=0x7ffff27e6004,      *pi=1024
ival=1024,      addr=0x7ffff27e6004

ppi=0x7ffff27e6008 ==> &pi=0x7ffff27e6008, pi=0x7ffff27e6004 ==> &ival=0x7ffff27e6004
```



#### 指向指针的引用

引用就是别名。

引用不是对象，所以不存在指向引用的指针。

但是指针是对象，所以存在对指针的引用。

```
int i=150;
int *p; //p是一个 int 型指针
int *&ref=p; //ref 是一个对指针p 的引用

ref=&i; //ref 被赋值，指向整数i，ref是p的别名，也就是p指向了i
*ref=-5;  //解引用ref得到i，也就是p指向的对象，将i的值改为-5
```

比较复杂的指针或引用声明语句，从右向左阅读，能搞清楚其真实含义。
- 距离变量 ref 最近的符号是 &，说明是引用。
- 前面有 * 说明是指针
- 配合前面的int，可以解释为 ref是 指向int的指针 的引用。落脚点是 指针的别名。

```
#include<iostream>
using namespace std;
int main(){
    //指向int的指针的引用
    int i=18;
    int *pd; //pd 是指向 int 的指针
    int *&ref=pd; //ref 是一个引用，指向int的指针的引用，也就是 ref 是 pd 的别名。

    ref=&i; //ref 的值是 i 的地址
    *ref=8;  // 解地址后就是i，修改i为8
    cout << "i=" << i << endl;
    cout << "ref=" << ref << ", pd=" << pd << ", *pd=" << *pd << endl;
    return 0;
}

$ g++ a14_ref_to_pointer.cpp 
$ ./a.out 
i=8
ref=0x7fff0bc790e4, pd=0x7fff0bc790e4, *pd=8
```









## 2.4 const 限定符

const 修饰后的变量不能被修改，所以必须初始化。可以使用任何表达式初始化。

```
const int i= get_size();
const int j=42;
const int k;  //错误，没有初始化
```


#### 修改 const 限定的变量会报错
```
$ cat b1_const.cpp
#include<iostream>
int main(){
    const int buf_size=1024;
    //buf_size=2048; //assignment of read-only variable ‘buf_size’
    return 0;
}
```


> 如果想在多文件共享 const 对象，就必须在变量的定以前加 extern 关键字。
```
// file1.cpp
extern const int bufSize= getSize();

// file1.h
extern const int bufSize; //与 file1.cpp 中定义的是同一个 bufSize
```





### const 的引用
```
$ cat b1_const2.cpp
#include<iostream>
int main(){
    const int buf_size=1024;
    const int &ref=buf_size; //正确，引用及其对应的对象都是常量

    //int &ref2=buf_size; //错误，引用不是常量
    //error: binding reference of type ‘int&’ to ‘const i discards qualifiers

    //ref=512; //错误，引用就是别名，常量不能修改。
    // error: assignment of read-only reference ‘ref’
    
    return 0;
}
```



#### 初始化和对 const 的引用


> 意外：const修饰的r1，其值竟然被改变了。

```
#include<iostream>
using namespace std;

// 使用变量初始化 const 值
int main(){
    int i=125;
    const int &r1=i; //允许将 const int &绑定到一个int对象上
    const int &r2=120;  //正确，r2是一个常量引用
    const int &r3=r1*2; //正确，r3是一个常量引用
    
    //int &r4= r1*2; //错误，r4是一个普通的非常量引用。
    // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

    cout << "r1=" << r1 << ", r2=" << r2 << ", r3=" << r3 << endl;

    //改变i的值，r1的值竟然也变了！
    i=-80;
    cout << "r1=" << r1 << ", r2=" << r2 << ", r3=" << r3 << endl;

    //r1 是常量引用，不能直接修改
    //r1=2; //error: assignment of read-only reference ‘r1’

    return 0;
}

$ g++ b2_const_init.cpp 
$ ./a.out 
r1=125, r2=120, r3=250
r1=-80, r2=120, r3=250
```


> 难点：const 修饰的变量不能直接修改，但可以间接修改，比如修改原来的变量，或其他非const的引用。

```
#include<iostream>
using namespace std;

int main(){
    int i=2;
    int &r1=i;   //r1绑定对象i
    const int &r2=i;  //r2页绑定对象i，但是不允许修改r2的值

    cout << "1 i=" << i << ", r1=" << r1 << ", r2=" << r2 << endl;

    i=10; //修改后，r1和r2都变了
    cout << "2 i=" << i << ", r1=" << r1 << ", r2=" << r2 << endl;

    r1=0; //r1不是常量，i的值为0
    //r2=0; //报错，r2不能修改。
    // error: assignment of read-only reference ‘r2’
    cout << "3 i=" << i << ", r1=" << r1 << ", r2=" << r2 << endl;

    return 0;
}

$ g++ b2_const_init2.cpp 
$ ./a.out 
1 i=2, r1=2, r2=2
2 i=10, r1=10, r2=10
3 i=0, r1=0, r2=0
```






### 指针和const





