#include<iostream>

using namespace std;

int main(){
    int a1=120;
    int *pd=&a1; //正确：初始值是 int 型对象的地址
    int *pd2= pd; //正确: 初始值是 指向 int 对象的指针

    //double *pi=a1; //错误：指针pi的类型与变量a1的类型不匹配
    // invalid conversion from ‘int’ to ‘double*’

    cout << "a1=" << a1 << " | addr=" << &a1 << endl;
    cout << "pd=" << pd << " | addr=" << &pd << ", val=" << *pd << endl;
    cout << "pd2=" << pd2 << " | addr=" << &pd2 << ", val=" << *pd2 << endl;
    //cout << "pi=" << pi << " | addr=" << &pi << endl;
    return 0;
}