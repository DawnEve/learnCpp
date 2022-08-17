#include<iostream>
using namespace std;

//返回类内定义的类型别名，作用域范围处理
class A{
public:
    using pos = int;
    pos &get();
private:
    pos x=8;
};

A::pos &A::get(){
    return x;
}

int main(){
    A a;
    cout << a.get() << endl;
    return 0;
}