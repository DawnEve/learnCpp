#include<iostream>
using namespace std;

//未提供默认构造函数的类类型，必须提供初始化值
class A{
public:
    A(int i): x(i){} //没有默认构造函数
    void show(){cout << "A::x=" << x << endl;}
private:
    int x;
};

class B{
public:
    B()=default; //提供默认构造函数了
    B(A ia, int iy): a(ia), y(iy){}
    void show(){ a.show(); cout << "B::y=" << y << endl; }
private:
    A a;
    int y;
};

int main(){
    //B b0; // error: no matching function for call to ‘A::A()’
    A a(10);
    B b(a, 3);
    a.show();
    b.show();
    return 0;
}