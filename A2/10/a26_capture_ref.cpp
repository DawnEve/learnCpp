#include<iostream>
using namespace std;

// lambda 表达式捕获值，是在创建时捕获，而不是调用时。

void demo1(){
    int v2=10; //局部变量
    auto f=[&v2](){ return v2;}; //返回的是引用

    v2=-12; //新的值
    //auto j=f();
    cout << f() << endl; //-12 一直是最新的值
}

int main(){
    demo1();

    return 0;
}
