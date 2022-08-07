#include<iostream>
using namespace std;

// 返回函数局部变量的指针或引用，将报错
int *fn1(){
    int i=5;
    return &i;
    // warning: address of local variable ‘i’ returned
}

int main(){
    int *p=fn1();
    cout << *p << endl; // 运行时错误: Segmentation fault (core dumped)

    return 0;
}