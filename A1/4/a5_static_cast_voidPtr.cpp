#include<iostream>
using namespace std;

//找回 void* 中保存的值
int main(){
    double d=1.2;
    void *p=&d; //正确：任何非常量对象的地址都可以存入 void*

    //该指针中保存的有地址，但是不能解引用。
    cout << p << endl;
    //cout << *p << endl; //error: ‘void* is not a pointer-to-object type

    //如果想读出来值，需要指定变量类型
    double *dp=static_cast<double*>(p);
    cout << dp << endl;
    cout << *dp << endl; 

    //如果类型不符呢
    int *ip=static_cast<int*>(p);
    cout << ip << endl;
    cout << *ip << endl; 

    return 0;
}