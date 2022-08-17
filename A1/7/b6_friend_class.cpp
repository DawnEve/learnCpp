#include<iostream>
using namespace std;

//A是B的友元类，则A能访问B的私有成员
class A;
class B;
class C;

class B{
    //声明B类的友元类：包括A
    friend class A;
public:
    void show(){ cout << "A.x=" << x << endl; }
private:
    int x=2;
};

class C{
public:
    void show(){ cout << "C.x=" << x << endl; }
private:
    int x=3;
};

class A{
public:
    void showB(B &b){ 
        b.show(); 
        cout << b.x << endl; //B和C的唯一区别，就是B的友元包括A，所以可以在A中访问B的私有成员。
    }
    void showC(C &c){ 
        c.show(); 
        //cout << c.x << endl; //error: ‘int C::x is private within this context
    }
};

int main(){
    A a;
    B b;
    C c;
    a.showB(b);
    a.showC(c);

    return 0;
}