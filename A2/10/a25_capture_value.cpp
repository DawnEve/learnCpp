#include<iostream>
using namespace std;

// lambda 表达式捕获值，是在创建时捕获，而不是调用时。

void demo1(){
    int v1=10; //局部变量
    auto f=[v1](){ return v1;}; //将v1拷贝到名为f的可调用对象

    v1=-12; //新的值，不影响调用
    //auto j=f();
    cout << f() << endl;
}

int main(){
    demo1();

    return 0;
}
