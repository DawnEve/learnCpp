#include<iostream>
using namespace std;

//必须自定义 默认构造函数的3个原因

// 1.只有不包含任何构造函数的类，编译器才会合成默认构造函数
class A{
public:
    A(int x){ cout << x << endl; }
};

// 2.默认初始化的值是不确定的
class B{
public:
    void get(){
        cout << x << " " << y << endl;
    }
private:
    int x;
    int y=25;
};

// 3. 编译器不能为某些类合成构造函数
class Book{
    public:
    Book(int x){}
};
class C{
    A a;
};

int main(){
    //A a1; //error: no matching function for call to ‘A::A()’

    B b2;
    b2.get(); //1815907360 25

    C c;

    return 0;
}