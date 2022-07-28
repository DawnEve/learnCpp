#include<iostream>
using namespace std;

int main(){
    // 赋值永远改变的是等号左侧的对象
    int ival=15;
    int ival2=35;
    int *pi= &ival; //初始化指针，指向的是 ival 的地址
    cout << &pi << " is addr of pi, value of pi=" << pi << ", point to *pi=" << *pi << endl;
    
    // 谁被改变了？
    pi=&ival2; //pi的值被改变了，现在pi指向 ival2
    cout << &pi << " is addr of pi, value of pi=" << pi << ", point to *pi=" << *pi << endl;

    *pi = 750; // *pi 被改变，也就是 pi 指向的值(ival2)变了，指针变量中保存的地址没变
    cout << &pi << " is addr of pi, value of pi=" << pi << ", point to *pi=" << *pi << endl;
    cout << "ival=" << ival << ", ival2=" << ival2 << endl;

    return 0;
}