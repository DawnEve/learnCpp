#include<iostream>
using namespace std;

//返回引用的函数作为左值

class A{
    int number;
    public:
    A(int x){number=x;}
    int getN() const { return number;}

    A &combine(A &rhs){
        number += rhs.getN();
        return *this;
    }
};

int main(){
    A a1(1), a2(20), a3(100);
    // 函数作为左值，因为函数返回的是引用
    a1.combine(a2).combine(a3); //可以链式调用下去

    cout << "a1=" << a1.getN() << endl;
    cout << "a2=" << a2.getN() << endl;
    cout << "a3=" << a3.getN() << endl;
    
    return 0;
}