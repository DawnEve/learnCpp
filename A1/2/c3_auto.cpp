#include<iostream>
using namespace std;

//使用auto初始化，初始值必须是同一种类型
int main(){
    int i=20, &r=i;
    const int ci=i, &cr=ci;

    auto k=ci, &l=i; //k 是整数，l是整型的引用
    auto &m=ci, *p=&ci; //m是对整型常量的引用，p是指向整型常量的指针

    //auto &n=i, *p2=&ci; // 错误：i的类型是int，而 &ci 的类型是 const int
    //error: inconsistent deduction for ‘auto’: ‘int’ and then ‘const int’

    return 0;
}