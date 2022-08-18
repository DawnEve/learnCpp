#include<iostream>
using namespace std;

//默认初始化 3
struct A{
    int i;
};

struct B{
    A a;
    int j;
    B(int x): j(x){}
};

int main(){
    B b1(5), b2(10);
    cout << b1.j << "\t" << b1.a.i << endl;
    cout << b2.j << "\t" << b2.a.i << endl;

    return 0;    
}