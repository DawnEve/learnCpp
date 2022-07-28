#include<iostream>
using namespace std;

// void* 指针，不能直接去之。
// 仅仅能比较是否相等、作为函数的输入或输出，或者赋值给另一个void*指针所指的对象。

int main(){
    double obj=3.14, *pd=&obj;
    cout << "obj=" << obj << ", &obj=" << &obj << endl;
    cout << "*pd=" << *pd << ",   pd=" << pd << endl;

    void *pv =&obj; 
    cout << "1 pv=" << pv << endl;
    //cout << "pv=" << pv << ", *pv=" << *pv << endl;
    // error: ‘void* is not a pointer-to-object type

    pv=pd;
    cout << "2 pv=" << pv << endl;

    int a1=100;
    pv=&a1;
    cout << "3 pv=" << pv << endl;

    return 0; 
}