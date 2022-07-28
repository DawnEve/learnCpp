#include<iostream>
using namespace std;

// 生成空指针的方法
int main(){
    int *p1=nullptr; //等价于 int *p1=0; (推荐)
    int *p2=0; //直接将p2初始化为字面量0
    //需要首先 #include cstdlib
    int *p3=NULL; //等价于 int *p3=0

    int zero=0;
    //int *p4=zero; //invalid conversion from ‘int’ to ‘int*’
    // 直接把0赋值给指针可以，但是把int变量赋值给指针不行，即使它的值是0.

    cout << "value of null pointer: p1=" << p1 << endl;
    cout << "value of null pointer: p2=" << p2 << endl;
    cout << "value of null pointer: p3=" << p3 << endl;
    // 访问空指针的值报错
    //cout << "value of null pointer: *p1=" << *p1 << endl; //Segmentation fault (core dumped)
    return 0;
}