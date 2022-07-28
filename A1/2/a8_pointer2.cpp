#include<iostream>

using namespace std;

//全局下的指针会自动初始化，局部下的不会。
int *p1;

int main(){
    int a1 = 220;
    int *p2; //未初始化，指向的内容不确定
    cout << "addr of a1: " << &a1 << endl;
    cout << "p1=" << p1 << endl;
    cout << "p2=" << p2 << " | value=" << *p2 << endl;

    p2=&a1;
    cout << "p2=" << p2 << " | value=" << *p2 << endl;

    return 0;
}