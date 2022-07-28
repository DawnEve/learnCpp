#include<iostream>
using namespace std;
int main(){
    //指向int的指针的引用
    int i=18;
    int *pd; //pd 是指向 int 的指针
    int *&ref=pd; //ref 是一个引用，指向int的指针的引用，也就是 ref 是 pd 的别名。

    ref=&i; //ref 的值是 i 的地址
    *ref=8;  // 解地址后就是i，修改i为8
    cout << "i=" << i << endl;
    cout << "ref=" << ref << ", pd=" << pd << ", *pd=" << *pd << endl;
    return 0;
}