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