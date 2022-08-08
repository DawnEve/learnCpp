#include<iostream>
using namespace std;

int arr[]={0,1,2,3,4};

//返回数组指针
int (*func(int i))[5]{
    arr[0] += i; //使用全局变量

    return &arr;
    //如果不使用全局变量，而是函数内定义 arr，
    //   则运行时报错，编译时警告: warning: address of local variable ‘arr’ returned 
}

int main(){
    int (*p)[5]=func(10); //返回的是指针，获取的也是指针
    const int (*p2)[5]=func(5); //加const后，有啥变化？

    //查看地址
    cout << "1 addr &arr: " << &arr << endl;
    cout << "2 addr p   : " << p << ", &p :" << &p << endl;
    cout << "3 addr p2  : " << p2 << ", &p2:" << &p2 << endl;

    //修改值
    arr[1]=100;
    (*p)[2]=200;
    //(*p2)[2]=700; //加const后不能用该指针修改指向的值，但是可以修改本身的值，是底层const
    //error: assignment of read-only location ‘*(p2 + 40)’
    int arr3[]={0,-1,-2,-3,-4};
    cout << "4 addr p2:" << p2 << endl;
    p2= &arr3; //修改指针本身的值
    cout << "5 addr p2:" << p2 << endl;

    //使用函数作为左值
    (*func(0))[3]=300;
    
    // 遍历
    for(auto i : *p)
        cout << i << " ";
    cout << endl;

    return 0;
}