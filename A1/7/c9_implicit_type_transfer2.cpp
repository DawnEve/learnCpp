#include<iostream>
using namespace std;

//隐式类型转换：靠构造函数，可以把一个类转为另一个类，则两类可以混用。
class A{
public:
    A(int i=10): x(i) {}
    int get(){return x;}
private:
    int x;
};

int main(){
    A a1, a2(20);
    cout << &a1 << ", a1.x=" << a1.get() << endl;
    a1=a2;
    cout << &a1 << ", a1.x=" << a1.get() << endl;
    a1=105;
    cout << &a1 << ", a1.x=" << a1.get() << endl;

    return 0;
}