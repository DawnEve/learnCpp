#include<iostream>
using namespace std;

// 定义
class A{
public:
    static constexpr int period = 30; // period 是一个常量表达式
};

// 一个不带初始值的静态成员的定义
constexpr int A::period; //初始值在类的定义内提供 
// 上一行：该定义可有可无。

int main(){
    A a;
    cout << a.period << endl;
    return 0;
}