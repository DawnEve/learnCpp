#include<iostream>
using namespace std;

//返回引用的函数作为左值

//返回大的值的引用
int &bigger(int &i1, int &i2){
    return i1>i2? i1: i2;
}

int main(){
    int a1=1, a2=20;
    // 函数作为左值
    bigger(a1, a2) = 5000; //把大的值修改为5000

    cout << "a1=" << a1 << endl;
    cout << "a2=" << a2 << endl;

    return 0;
}