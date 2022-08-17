#include<iostream>
using namespace std;

//友元声明不能代替函数声明，它们是相互独立的

class X{
public:
    friend void f(){ cout << "f()" << endl; }; //友元函数可以定义在类内部
    //X(){ f(); } //错误：f还没有被声明
    // error: ‘f was not declared in this scope
    void g();
    void h();
};

//void X::g(){ return f();} //错误: f还没有被声明
//error: ‘f was not declared in this scope

void f(); //函数声明
void X::h(){ return f();} //正确: 现在f的声明在作用域中可见了

int main(){
    X x;
    x.h();
}