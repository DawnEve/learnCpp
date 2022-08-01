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



## 4.12 运算符优先级表



> 2022.8.1
