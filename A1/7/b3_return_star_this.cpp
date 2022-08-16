#include<iostream>
using namespace std;

//返回*this

class A{
private:
    int i=0;
public:
    A()=default;
    A(int x): i(x){}
    A set(int x){ i = x; return *this;} //函数返回类型是本身，则发生复制
    A &cset(int x){i = x; return *this;} //函数返回类型是引用，则返回的是本身，无复制
    void show() const { cout << i << endl;}
};


int main(){
    A a1(1), a2(2);
    cout << "&a1:" << &a1 << ", &a2=" << &a2 << endl;
    A b1=a1.set(10);
    A &b2=a2.cset(20);
    const A &b3=a2.cset(300);
    a1.show();
    a2.show();
    b3.show();
    //可见，cset 返回的是引用，其地址和a2一样
    cout << "&b1:" << &b1 << ", &b2=" << &b2 <<", &b3=" << &b3 << endl;

    return 0;
}