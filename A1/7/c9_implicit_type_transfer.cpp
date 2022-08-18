#include<iostream>
using namespace std;

//隐式类型转换：靠构造函数，可以把一个类转为另一个类，则两类可以混用。
class A{
public:
    A(int i=10): x(i) {}
    A &combine(const A &a){
        x += a.x;
        return *this;
    }
    int get(){return x;}
private:
    int x;
};

int main(){
    A a1, a2(20);
    cout << "1 " << a1.get() << endl;
    a1.combine(a2);
    cout << "2 " << a1.get() << endl;
    a1.combine(30); // 这里的int 30 直接通过构造函数转为A类型：A(30)
    cout << "3 " << a1.get() << endl;
    // 变量也行
    int b=100;
    a1.combine(b);
    cout << "4 " << a1.get() << endl;

    return 0;
}