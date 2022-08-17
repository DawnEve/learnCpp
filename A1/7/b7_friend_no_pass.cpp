#include<iostream>
using namespace std;

//A是B的友元，B是C的友元，则A不能访问C的私有成员。
class A;
class B;

class C{
    friend class B; //B是C的友元类，B能访问C的私有成员
    int x=3;
};

class B{
    friend class A; //A是B的友元类, A能访问B的私有成员
    int x=2;
public:
    void showC(C &c){
        cout << c.x << endl; //在B中访问C的私有成员
    }
};

class A{
    int x=1;
public:
    void showB(B &b){
        cout << b.x << endl; //在A中访问B的私有成员
    }
    void showC(C &c){
        //cout << c.x << endl; //在A中 不能 访问C的私有成员
        // error: ‘int C::x is private within this context
    }
};

int main(){
    A a;
    B b;
    C c;
    b.showC(c);

    a.showB(b);
    //a.showC(c);

    return 0;
}