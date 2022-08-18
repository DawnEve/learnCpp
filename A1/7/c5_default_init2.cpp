#include<iostream>
using namespace std;

//默认初始化 2
struct A{
    int i;
};

struct B{
    A a;
};

int main(){
    B b1,b2, b3[5];
    for(int i=0; i<5; i++)
        cout << b3[i].a.i << endl;

    return 0;    
}