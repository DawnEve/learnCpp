# 2 变量和基本类型

`$ cd mkdir A1/2/`

## 2.1 内置类型

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










## 2.2 变量

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










## 2.3 复合类型 compound type

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

允许const修饰的常量初始化为一个变量。

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

允许一个指向常量的指针指向一个非常量对象。

```
#include<iostream>
using namespace std;

int main(){
    const double pi=3.1415;

    //存放常量对象的地址，需要指向常量的指针
    //double *ptr=&pi; //错误：ptr是一个普通指针
    // error: invalid conversion from ‘const double*’ to ‘double*’ [-fpermissive]

    const double *cptr=&pi; //正确，cptr是一个指向双精度常量的指针
    //*cptr=10; //错误，不能给 const 修饰的常量赋值
    //error: assignment of read-only location ‘* cptr’

    cout << "cptr=" <<cptr << ", *cptr=" << *cptr << endl;

    return 0;
}

$ g++ b3_const_pointer.cpp 
$ ./a.out 
cptr=0x7ffddda93c68, *cptr=3.1415
```

> 例外情况，指向常量的指针，可以指向一个常量，通过修改常量来修改指针所指的值。

```
#include<iostream>
using namespace std;

int main(){
    double pi=3.14;
    double pi2=3.1415926;
    const double *cptr;
    cptr=&pi;
    cout << "cptr=" << cptr << ", *cptr=" << *cptr << endl;

    cptr=&pi2; //也就是说const修饰的指针变量是可以修改的
    cout << "cptr=" << cptr << ", *cptr=" << *cptr << endl;

    //*cptr=10.2; //但是不能通过指针修改其所指的对象的值
    //error: assignment of read-only location ‘* cptr’

    return 0;
}

$ g++ b3_const_pointer2.cpp 
$ ./a.out 
cptr=0x7ffe652baf00, *cptr=3.14
cptr=0x7ffe652baf08, *cptr=3.14159
```

通俗解释：事项常量的指针或引用，不过是指针或引用的“自以为是”罢了，它们决定自己指向了常量，所以自觉的不去修改所指对象的值。但是这个值可以通过其他途径修改。




#### const 指针 

指针是对象，常量指针 (const pointer) 就是初始化后不能修改的指针对象。

- 语法：把*放到const前面，定义一个指针是一个常量： `double pi = 3.14; double *const cpi= &pi;`
- 指针变量中保存的那个地址不能修改，并不意味这该地址指向的值不能修改。
- 如果想让指针指向的那个对象也是只读的，前面再加一个 const: `const double *const cpi2=&pi;`


```
#include<iostream>
using namespace std;
int main(){
    double pi = 3.14; 
    double *const cpi= &pi; //看这个定义，从右向左阅读
    // 距离 cpi 最近的是 const，意味着 cpi 本身是常量，不能修改
    // 接着是 * 表示 cpi 是一个指针
    // 最后是 double 表示指针指向的是一个double变量，可以通过指针修改

    const double *const cpi2=&pi;
    //从右向左，这个最后的修饰符是一个 const，表示指针指向的也是一个常量，也不能通过指针修改。


    cout << "pi=" << pi << ", addr &pi=" << &pi << endl;
    cout << "1 cpi=" << cpi << ", value *cpi=" << *cpi << endl;
    
    //可以通过指针修改值
    *cpi=3.1415926;
    cout << "2 cpi=" << cpi << ", value *cpi=" << *cpi << endl;

    //不能修改指针中保存的地址
    double piLong=3.14159265358979;
    //cpi=&piLong; //指针变量中保存的地址 只读
    // error: assignment of read-only variable ‘cpi’

    //对于 cpi2则指针变量中的地址是常量，指针指向的对象也是常量
    //cpi2=&piLong; //error: assignment of read-only variable ‘cpi2’
    //*cpi2=3.1; //error: assignment of read-only location ‘*(const double*)cpi2’

    return 0;
}

$ g++ b3_const_pointer3.cpp 
$ ./a.out 
pi=3.14, addr &pi=0x7fff0a7bc878
1 cpi=0x7fff0a7bc878, value *cpi=3.14
2 cpi=0x7fff0a7bc878, value *cpi=3.14159
```










### 顶层 const

指针对象是不是常量，指针指向的对象是不是常量，是两个独立的问题。

- 顶层 top-level const 表示指针本身是一个常量。
    * 更一般的，**顶层 const** 可以表示任意的对象是常量，对任意类型都适用：算术类型、类、指针等。
- 底层 low-level const 表示指针所指的对象是一个常量。
    * **底层const** 则与指针和引用等符合类型的基本类型部分有关。

> 指针类型，既可以是顶层const，也可以是底层const。这一点和其他类型区别明显。


```
$ cat b4_const_level.cpp
#include<iostream>
using namespace std;
int main(){
    int i=150;
    int *const pi=&i; // 不能改变 pi 的值，顶层const
    const int ci=1024; // 不能改变 ci 的值，顶层const

    const int *p2=&ci; //允许改变p2的值，这个一个 底层const
    const int *const p3=p2; //靠右的const是顶层const，靠左的const是底层const
    const int &ref=ci; //用于声明引用的const都是底层const

    //当执行对象的拷贝时，常量是顶层const还是底层const区别明显。
    //1. 其中，顶层 const 不受什么影响。
    i=ci; //正确，拷贝 ci 的值，ci是一个顶层const，对此操作无影响
    p2=p3; // 正确：p2和p3指向的对象类型相同，p3顶层const的部分不影响
    //执行拷贝不改变被拷贝对象的值，所以拷如和考出的对象是否是常量没影响。

    //2. 底层const有限制：考入和烤出的对象必须具有相同的底层const资格，或者两个对象的数据类型能转换。
    // 非常量可以转为常量，反之不行。
    
    //int *p=p3; //错误: p3 包括底层const定义，而p没有
    // error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]

    p2=p3; //正确，p2和p3都是底层const
    p2=&i; //正确， int* 能转为 const int *

    //int &ref2=ci; //错误： 普通的 int & 不能绑定到 int 常量上
    //error: binding reference of type ‘int&’ to ‘const int’ discards qualifiers
    const int &ref3=ci; //正确， const int & 可以绑定到 const int 上

    const int &ref4=i; //正确， const int & 可以绑定到 普通 int 上
    
    return 0;
}
```





### constexpr 和常量表达式

c++中有些情况要用常量表达式，见后文。

常量表达式 (const expression) 是值不会改变，且在编译过程就能得到计算结果的表达式。


- 字面量
- 用常量表达式初始化的 const 对象也是常量表达式

```
const int max_files=20;  // max_files 是常量表达式
const int limit = max_files +1; // limit 是常量表达式

int staff_size=27; //staff_size不是常量表达式：数据类型是int，而不是 const int
const int sz=get_size(); //sz 不是常量表达式：尽管是常量，但是数值需要运行时才能获取到
```


由于很难区分是不是，C++11标准， constexpr 类型，由编译器验证变量是否是一个 常量表达式。

```
$ cat b6_constexpr.cpp
#include<iostream>
using namespace std;

int get_size(){
    return sizeof(int)*5;
}

int main(){
    // C++11
    constexpr int mf=20;
    constexpr int limit = mf+1;

    //constexpr int sz=get_size();
    // error: call to non-‘constexpr’ function ‘int get_size()’

    return 0;
}
```

> 你认定变量是一个常量表达式，那就优先声明为 constexpr 类型。





#### 字面值类型

函数内的变量地址不确定，不能用于定义 constexpr。


#### 指针和 constexpr

限定符 constexpr 仅对指针有效，对指针所指的对象无关。

```
const int *p = nullptr; //p 是一个指向 整型常量 的指针
constexpr int *q=nullptr; //q是指向整数的 常量指针
```









## 2.5 处理类型

### 类型别名 typedef

> 传统方法是 `typedef int INT2;`，新标准是 `using INT3 = int;`

```
#include<iostream>
using namespace std;

int main(){
    //1. typedef
    typedef int bookNumber; //bookNumber 是 int 的同义词。
    bookNumber book1=12;
    int book2=12;

    if(book1==book2)
        cout << "equal" << endl;

    //2. alias
    using int2=int; //int2 是 int 的别名
    int2 *p2=&book1;
    cout << "addr &book1=" << &book1 << ", p2=" << p2 << ", *p2="<< *p2 <<endl;

    return 0;
}
```


#### 指针、常量和类型别名

//todo jump, P61, pdf(87/864)







### auto 类型说明符

程序根据初始值确定类型。一条语句的类型必须一致。




#### 复合类型、常量和auto

编译器推断出来的auto类型有时候和初始值的类型并不完全一样，编译器会适当的改变结果使其更符合初始化规则。


- 首先，使用引用其实是使用引用的对象，特别是引用被用作初始值时，真正参与初始化的是引用对象的值。此时编译器以引用对象的类型作为auto的类型

```
int i=0, &r=i;
auto a=r; //a是一个整数(r是i的别名，而i是一个整数)
```

- 其次，auto 一般忽略掉 顶层const，同时保留底层const。比如当初始化一个指向常量的指针时。

```
const int ci=i, &cr=ci;
auto b=ci; //b是一个整数(ci的顶层const特性被忽略掉了)
auto c=cr; //c是一个整数(cr 是ci的别名，ci本身是一个顶层const)
auto d=&i; //d是一个整型指针（整数的地址就是指向整型的指针）
auto e=&ci; //e是一个指向整数常量的指针（对常量对象取地址是一种底层const）
```

//todo hard 不太懂，上例。

如果希望推断出 auto 类型是一个顶层 const，需要明确指出：

```
const auto f=ci; //ci 的推演类型是 int， f是 const int
```


还可以将引用的类型设为auto，此时原来的初始化规则仍然适用:

```
auto &g=ci; //g是一个整形常量的引用，绑定到ci
auto &h=42; //错误：不能为非常量引用绑定字面量
const auto &j=42; //正确：可以为常量引用绑定字面量
```


- 设置一个类型为auto的引用时，初始值中的顶层常量属性仍然保留。
- 如果给初始值绑定一个引用，则此时的常量就不是顶层常量了。

//todo hard, 不懂上面这两句 P62




要在一条语句中定义多个变量，切记：符号&和*只属于某个声明符，而非基本数据类型的一部分，因此初始值必须是同一种类型。

```
$ cat c3_auto.cpp
#include<iostream>
using namespace std;

//使用auto初始化，初始值必须是同一种类型
int main(){
    int i=20, &r=i;
    const int ci=i, &cr=ci;

    auto k=ci, &l=i; //k 是整数，l是整型的引用
    auto &m=ci, *p=&ci; //m是对整型常量的引用，p是指向整型常量的指针

    //auto &n=i, *p2=&ci; // 错误：i的类型是int，而 &ci 的类型是 const int
    //error: inconsistent deduction for ‘auto’: ‘int’ and then ‘const int’

    return 0;
}
```









### decltype 类型指示符

C++11新标准。

- 目的：从表达式的类型推断要定义的变量的类型。
- 编译器分析，但是不计算。

```
decltype (f()) sum=x; // sum 的类型就是函数 f 的返回值
```

- decltype 处理顶层const和引用的方式与auto不同。
    * 如果 decltype 使用的表达式是一个变量，则 decltype 返回该变量的类型（包括顶层const 和 引用在内）

```
const int ci=0, &cj=ci;
decltype(ci) x=0; //x 的类型是 const int
decltype(cj) y=x; //y 的类型是 const int&, y绑定到变量x
decltype(cj) z; //错误：z是一个引用，必须初始化
```

> 注意，引用从来都是作为所指对象的同义词出现，只有在 decltype 处是一个例外。



#### decltype 和引用

- 如果 decltype 使用的表达式不是一个变量，则 decltype 返回表达式结果对应的类型。
- P120: 有些表达式将向 decltype 返回一个引用类型。
    * 一般，这意味着该表达式的结果对象能作为一条赋值语句的左值。

```
//decltype 的结果可以使引用类型

int i=42, *p=&i, &r=i;
decltype(r+0) b; //正确：加法的结果是int，因此b是一个(未初始化的) int
decltype(*p) c;  //错误: c是 int&, 必须初始化
```

> 如果表达式的内容是解引用操作，则 decltype 将得到引用类型。

- 因为 解引用指针可以得到指针所指的对象，而且还能给这个对象赋值。
- 因此，`decltype(*p) 的结果类型是 int&`，而非 int。

```
#include<iostream>
using namespace std;

//decltype 获得的是不是引用，怎么区分？
// 能获得值，能修改值，则是引用，是引用就要初始化。

int main(){
    int i=42, *p=&i, &r=i;
    decltype(r+0) b; //正确：加法的结果是int，因此b是一个(未初始化的) int
    
    //decltype(*p) c;  //错误: c是 int&, 必须初始化
    // error: ‘c declared as reference but not initialized

    b=20;
    cout << b << endl;

    return 0;
}

$ g++ c1_decltype.cpp 
$ ./a.out 
20
```


decltype 和 auto 的另一个重要区别是，decltype 的结果类型与表达式形式密切相关。

- 对于 decltype 所用的表达式来说，如果变量名加上一对括号，则得到的类型与不加括号时会有不同。
    * 如果使用不加括号的变量，则得到的类型就是该变量的类型；
    * 如果变量加了一层或多层括号，则编译器会把它当成是表达式。 变量是一种可以作为赋值语句左值的特殊表达式，所以这样的decltype 就会得到引用类型：

```
#include<iostream>
using namespace std;

// 变量，加括号的变量，得到的类型是不同的
int main(){
    int i=10;

    decltype(i) d; //正确，d是一个未初始化的 int
    //decltype((i)) e; //错误，e是一个int&，必须初始化
    //error: ‘e declared as reference but not initialized

    int num=10;
    decltype((i)) e=num; //绑定变量
    e=200;
    cout << num << endl;

    return 0;
}

$ g++ c2_decltype2.cpp 
$ ./a.out 
200
```

> 切记： decltype( (variable) ) （注意是双层括号）的结果永远是引用，而 decltype(variable) 的结果只有当 variable 本身是引用时才是引用。










## 2.6 自定义数据结构

### 定义 Sales_data 类型

使用 struct 定义结构体，暂时代替 class(第7章介绍 类)。

```
//方式1: 定义和实体化一行
struct Sales_data2 { /**/ } accum2, trans2, *salesptr2;

//方式2: 定义和初始化分开，推荐
struct Sales_data3 { /**/ };
Sales_data3 accum3, trans3, *salesptr3;
```

一个完整例子：
```
#include<iostream>

using namespace std;

struct Sales_data{
    std::string bookNo;
    unsigned units_sold=0;
    double price=0.0;

    double revenue=0.0;
}; //记得分号结尾

int main(){
    Sales_data data1, data2, *salesPtr;
    double price=0.0; //书的总价

    cout << "Input ISBN units_sold price" << endl;
    //1.读数据
    cin >> data1.bookNo >> data1.units_sold >> data1.price;
    data1.revenue = data1.units_sold * data1.price;
    //
    cin >> data2.bookNo >> data2.units_sold >> data2.price;
    data2.revenue = data2.units_sold * data2.price;

    //2.判断isbn是否相同
    if(data1.bookNo == data2.bookNo){
        //3.如果相同，则求和，输出总本书,总金额,均价。
        unsigned totalCnt=data1.units_sold+data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        // 输出: isbn, 总销量，中销售额，均价
        cout << data1.bookNo << "\t" << totalCnt << "\t" << totalRevenue << "\t";
        if(totalCnt!=0){
            cout << totalRevenue/totalCnt << endl;
        }else{
            cout << "No sales" << endl;
        }
        return 0;
    } else {
        cerr << "Data must refer to the same ISBN" << endl;
        return -1;
    }
}

$ g++ b8_struct.cpp 
$ ./a.out 
Input ISBN units_sold price
X1 3 20
X1 4 15
X1      7       120     17.1429
```



### 编写自己的头文件

- 为了一次定义类，其他文件都能用，所以必须使用头文件。
- 为了一致，Salse_data 类，一般定义在 Sales_data.h 的头文件中。
- 头文件也经常用到其他头文件的功能，比如 Sales_data.h 包含 string.h 头文件。
    * 而使用 Sales_data 类的程序，为了操作 bookNo 成员，需要再一次包含 string.h 头文件。
    * 怎么处理这种多次包含的情况？ 预处理



#### 预处理器 preprocessor

头文件保护符：
```
#ifndef XX_CLASS
#define XX_CLASS

/*...*/

#endif
```

- 预处理器无视作用域，它不属于C++语句，编译前完成替换
- 为了防止重名，保护符的名字使用类名加后缀，一般全大写，确保唯一性。
- 建议都加上头文件保护符，不管需不需要。

```
$ cat b9_preprocessor.h
#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>
struct Sales_data{
    std::string bookNo;
    unsigned units_sold=0;
    double price=0.0;

    double revenue=0.0;
}; //记得分号结尾

#endif
```






> 2022.7.29
