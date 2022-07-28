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