#include<iostream>
using namespace std;

// 打印函数内外的this地址
class A{
    public:
    void getAddr(){
        cout << "in :" << this << endl;
    }
};

int main(){
    A a1;
    cout << "out:" << &a1 << endl;
    a1.getAddr();
    return 0;
}