#include<iostream>
using namespace std;

int main(){
    int val=125;
    int *pA = &val; //pA 存放的是 val 的地址，或者说 pA 是指向变量 val 的指针

    cout << "val=" << val << ", *pA=" << *pA << endl;

    //赋值
    *pA=-80; //给pA的解引用，也就是pA指向的地址赋值
    cout << "val=" << val << ", *pA=" << *pA << endl;

    return 0;
}