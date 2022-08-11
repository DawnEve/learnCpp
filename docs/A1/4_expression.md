# 第四章 表达式

## 4.1 基础

- 一元运算符： 取地址&, 解引用*；
- 二元运算符：==，*；
- 三元运算符: ?:

运算符重载：对已有运算符的新类型，重新定义运算规则。

### 优先级与结合律

- 括号优先级最高。

### 求值顺序





## 4.2 算术运算符

- 求余数 %
- 溢出和其他算术运算异常






## 4.3 逻辑和关系运算符

- 逻辑与 `&&`
- 逻辑或 `||`




## 4.4 赋值运算符


## 4.5 递增和递减运算符

- 前置版本 `j=++i;` 得到递增之后的值;
- 后置版本 `j=i++;` 得到递增值前的值.

> 建议： 除非必要，不要使用递增、递减运算符的后置版本。


> 后置递增运算符的优先级高于解引用，所以 `*p++` 等价于 `*(p++)`：指针先移动到下一个位置，然后返回递增前的位置，再取值。

- 基于一个事实：后置递增返回的是递增前的指针。否则，递增后的指针返回，则解引用会报错，无法输出第一个元素。

> 建议：简洁可以成为一种美德。 `cout << *p++ << endl; ` 比 `cout << *p << endl; ++p;` 更简洁，且不容易出错。



```
#include<iostream>
using namespace std;

// *p++ 等价于 *(p++)
int main(){
    int arr[]={10,1,2,3,4,5};
    int *p=arr;

    while(p != end(arr)){
        cout << *p++ << endl;
    }
    return 0;
}


$ g++ a1_ptr_increase.cpp 
$ ./a.out 
10
1
2
3
4
5
```






## 4.6 成员访问运算符

> 点运算符和箭头运算符都可以访问成员：`(*ptr).mem` 等价于 `ptr->mem`，其中ptr是指针。

- 指针 + 箭头运算符，结果是一个左值。
- 指针 + 点运算符，如果成员所属的对象是左值，结果是左值；如果成员所属的对象是右值，结果是右值。


```
#include<iostream>
using namespace std;

int main(){
    // 取成员变量，使用点或者箭头都是可以的
    string s1="this is a book", *p=&s1;
    auto n=s1.size(); //运行 string 对象 s1 的 size 成员函数

    cout << (*p).size() << endl;
    cout << p->size() << endl;

    // 圆括号必须有
    //cout << *p.size() << endl; //因为解引用的优先级低于点，指针没有点运算，报错
    //  error: request for member ‘size’ in ‘p’, which is of pointer type ‘std::string*’ 
    // {aka ‘std::__cxx11::basic_string<char>*’} (maybe you meant to use ‘->’ ?)

    return 0;
}


$ g++ a2_dot_array.cpp 
$ ./a.out
14
14
```







## 4.7 条件运算符

- `cond? expr1: expr2;`
- `string finalgrade = (grade<60)? "faile": "pass";`
- 支持嵌套。






## 4.8 位运算符

//todo jump P136, pdf(162/864)





## 4.9 sizeof 运算符

- 两种形式：`sizeof (type)` 和 `sizeof expr`


```
#include<iostream>
using namespace std;

//的两种形式 sizeof(type) 和 sizeof expr

struct Book{
    string bookNo="";
    int number=0;
    double price=0.0;
};

int main(){
    Book book1, *p;

    cout << sizeof(Book) << endl; //存储 Book 类型的对象所占的空间大小

    cout << sizeof(book1) << endl; // book1 的类型的大小，即 sizeof(Book)
    cout << sizeof *p << endl; //所指类型的大小

    cout << sizeof p << endl; // 8 指针所占空间大小
    cout << sizeof book1.number << endl; //4
    cout << sizeof Book::number << endl; //4

    return 0;
}


$ g++ a3_sizeof.cpp 
$ ./a.out 
48
48
48
8
4
4
```




## 4.10 逗号运算符


## 4.11 类型转换

//todo jump


### 显式转换

> 虽然有时不得不用强制类型转换，但是这种方法本质上是非常危险的。

```
// 执行整数的浮点数除法
int i, j;
double slope = i/j;
```





#### 命名的强制类型转换

- 形式：`cast-name <type>(expression);`
- 其中，type是转换的目标类型，expression是要转换的值。如果type是引用类型，则结果是左值。
- cast-name 是 `static_cast`、`dynamic_cast`、`const_cast` 和 `reinterpret_cast` 中的一种。指定了执行哪种转换。


#### static_cast

任何具有明确定义的类，只要不包含底层 const，都可以使用 static_cast。

```
// 强制转为浮点数，以便进行浮点数除法
double slope=static_cast<double>(j) / i;
```

当需要把较大的算术类型赋值给较小的类型时， static_const 就是在告诉编译器：我不在与潜在的精度损失。

一般，编译器发现一个较大的算术类型试图赋值给较小的类型时，就会给出警告信息；但是执行了显式的类型转换后，警告信息就消失了。

为什么没看到warning？ //todo

```
#include<iostream>
using namespace std;

//强制类型转换：大的算术类型赋值给小的类型时
int main(){
    int j=10, i=3;
    double dj=12345678910.5;

    short slope0 = dj / i; //无警告
    long double slope1 = (double)j / i; //C风格的
    double slope = static_cast<double>(j) / i;

    cout << slope0 << endl;
    cout << slope1 << endl;
    cout << slope << endl;

    j= dj - 12345678908.66; //没看到啥warning
    cout << j << endl;

    return 0;
}

$ g++ -Wall a4_static_cast.cpp 
$ ./a.out 
0
3.33333
3.33333
1
```


- static_cast 可以用于编译器无法自动执行的类型转换。比如找回 void* 指针种的值。
- 转换后，指针保存的地址是不变的，只是恢复了之前的正确类型。
- 如果类型不对，将产生未定义后果(就是值按内存规则读取后，不符合预期)。

```
#include<iostream>
using namespace std;

//找回 void* 中保存的值
int main(){
    double d=1.2;
    void *p=&d; //正确：任何非常量对象的地址都可以存入 void*

    //该指针中保存的有地址，但是不能解引用。
    cout << p << endl;
    //cout << *p << endl; //error: ‘void* is not a pointer-to-object type

    //如果想读出来值，需要指定变量类型
    double *dp=static_cast<double*>(p);
    cout << dp << endl;
    cout << *dp << endl; 

    //如果类型不符呢
    int *ip=static_cast<int*>(p);
    cout << ip << endl;
    cout << *ip << endl; //值将是错误的，怎么从内存角度预测这个结果？ //todo

    return 0;
}

$ g++ a5_static_cast_voidPtr.cpp 
$ ./a.out 
0x7ffe6ab58aa8
0x7ffe6ab58aa8
1.2
0x7ffe6ab58aa8
858993459
```


#### const_cast 

const_cast 只能改变运算对象的低层 const (P57)。

```
const char *cp;
char *p = const_cast<char *>(cp); //正确，但是通过p写值是未定义的行为
```


例: 打印char的地址。

```
#include<iostream>
using namespace std;

// 获取字符的地址
//https://blog.csdn.net/Master_0_/article/details/123793762
int main(){
    char s1='c', s2='x';
    cout << &s1 << endl; //获取地址，为什么总是失败？ 因为cout总是想把字符读取到\0结尾为止

    //check
    char arr[]={'h', 'i', ',', '\0'};
    cout << &(arr[0]) << endl; //想要第一个字符的地址，但是一直输出字符，直到 \0 才停止
    cout << (void *)&(arr[0]) << endl; //第一个字符的地址

    //solution
    printf("method1: &s1=%p\n", &s1); //方法1: 使用C的printf
    cout << "method2: &s1=" << (void *)&s1 << endl; //方法2: 强制转为空指针

    return 0;
}

$ g++ a6_print_char_address.cpp 
wangjl@YStation:~/data/project/learnCpp/A1/4$ ./a.out 
cx
hi,
0x7ffe12240014
method1: &s1=0x7ffe12240012
method2: &s1=0x7ffe12240012
```


例2: const_cast 强转 const char* 为 char*

```
#include<iostream>
using namespace std;

// const_cast 只能改变运算对象的低层const
int main(){
    char s1='c', s2='x';
    const char *cp = &s1; //从右向左读：cp是一个指针；指向一个char类型；指向的char值是常量
    //修改
    s1='b';
    
    //*cp='a'; //底层const，指向的值只读，不能通过该指针写其指向的值。
    //error: assignment of read-only location ‘* cp’ 
    cp=&s2; //但可以修改该指针中的地址
    //*cp='y'; //只读，通过指针不能修改其指向的值
    
    cout << "1 " << s1 << endl;
    cout << "2 " << *cp << endl;

    //修改指针类型，看能否只读变读写
    char *p = const_cast<char *>(cp); //正确，但是通过p写值是未定义的行为？//todo 什么叫未定义的行为？
    cout << "3 cp:" << (void *)cp  << ", p:" << (void *)p << endl; //强转后，指针中保存的地址不变
    // 打印字符的地址，见上一个示例: a6

    cout << "4 " << *p << endl;

    //修改值
    *p='z';
    cout << "5 " << *p << endl;
    cout << "6 " << s2 << endl;

    return 0;
}

$ g++ a7_const_cast.cpp 
$ ./a.out 
1 b
2 x
3 cp:0x7ffd2ee77177, p:0x7ffd2ee77177
4 x
5 z
6 z
```

- 只有 const_cast 能改变表达式的常量属性，使用其他形式的命名强制类型转换改变表达式的常量属性都将引发编译器错误。
- 同样的，也不能使用 const_cast 改变类型。

```
const char *cp = &s1;
char *q = static_cast<char*>(cp); //错误: static_cast 不能把 const 去掉
string s2= static_cast<string>(cp); //正确：字符串字面值转换成string类型
string s3= const_cast<string>(cp); //错误: const_cast 只能修改const属性
```

例:

```
#include<iostream>
using namespace std;

// const_cast 只能改变 const 属性，不能改其他类型。
int main(){
    char s1= 'c', *ps1=&s1;
    const char *cp = &s1;

    //char *q = static_cast<char*>(cp); // error: invalid static_cast from type ‘const char*’ to type ‘char*’
    char *q = const_cast<char*>(cp);
    cout << *q << endl;

    // 转为字符串类型
    string s2= static_cast<string>(cp); //正确：字符串字面值转换成string类型
    cout << s2 << endl;

    //string s3= const_cast<string>(cp); //错误: const_cast 只能修改const属性
    char *p3= const_cast<char*>(cp);
    *p3='d';
    cout << *q << endl;

    return 0;
}

$ g++ a8_const_cast_err.cpp 
$ ./a.out 
c
c
d
```

> const_cast 常用欧冠与函数重载(P208)的上下文中。





#### reinterpret_cast

通常为运算对象的位模式提供较低层次上的重新解释。

//todo 不太懂

```
int i=8, *ip=&i;
char *pc = reinterpret_cast<char*>(ip);
```
- 牢记pc指向的真实对象是一个int而非字符，如果把pc当成普通的字符指针使用则可能在运行时发生错误。

`string str(pc);` 会导致异常的运行时行为。

- 使用 reinterpret_cast 是非常危险的。 //todo 没看懂危险在哪里？ P146

> 警告: reinterpret_cast 本质上依赖于机器。要想安全的使用 reinterpret_cast 必须对涉及的类型和编译器实现转换的过程都非常了解。

> 建议：避免强制类型转换。 在函数重载时使用 const_cast 无可厚非，其他地方使用const_cast，则意味着程序有某种设计缺陷。其他强制类型转换，比如 static_cast, dynamic_cast 都不应该频发使用。每一次使用都要反复斟酌能否用其他反式实现相同的目标。如果无法避免，也应该极可能限制类型转换的作用域，并记录相关类型的所有假设，这样可以减少错误发生的机会。



```
#include<iostream>
using namespace std;

// reinterpret_cast 是很危险的
int main(){
    int i=65, *ip=&i;
    char *pc = reinterpret_cast<char*>(ip);

    cout << "1 " << *pc << endl;
    string str(pc);
    cout << "2 " << str << endl;

    char *pc2 = (char*) ip; //ip是指向的是整数的指针
    printf("3 %c\n", *pc2);
    cout << "4 " << *pc2 << endl;

    return 0;
}


$ g++ a9_reinterpret_cast.cpp 
$ ./a.out 
1 A
2 A
3 A
4 A
```



#### 旧式的强制类型转换

早期的C++语言中，显式强转包含2种形式:

```
type (expr); //函数形式的强制类型转换
(type) expr; //C语言风格的强制类型转换
```

```
int i=8, *ip=&i;
char *pc = (char*) ip; //ip是指向整数的指针
```

- 如果替换成 const_cast 和 static_cast 也合法，行为与对应的命名转换一致。
- 如果替换后不合法，则与 reinterpret_cast 类似，效果和使用 reinterpret_cast 一样。

> 旧式的区分不明确，出问题时不好追踪，建议用新的形式进行强转。









## 4.12 运算符优先级表



> 2022.8.1
> 2022.8.11 强制类型转换
