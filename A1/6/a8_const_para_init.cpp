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