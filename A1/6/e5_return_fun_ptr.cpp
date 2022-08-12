#include<iostream>
using namespace std;

//返回函数指针的函数：依据输入int的正负，返回一个指针，指向以下2个函数中的一个

int getMax(int *p1, int *p2){
    return *p1>*p2 ? *p1 : *p2;
}

int getMin(int *p1, int *p2){
    return *p1<*p2 ? *p1 : *p2;
}


//method1 直接声明: 最难理解的形式
int (*pf1(int n))(int*, int*){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}
/*
从内到外拆开理解
* 最核心的 pf1(int n) 说明是一个函数，形参列表是 int n
* 前面有星号，表示其返回值是一个指针
* 看右侧：指向的函数的形参列表(int*, int*)
* 看左侧：指向的函数的返回值是 int
*/

//method2: 使用类型别名
using Fun = int(int*, int*); //函数类型
using pFun = int(*)(int*, int*); //指向函数的指针

Fun *pf2(int n){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}

pFun pf2_(int n){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}

//C风格的类型别名
typedef int Fun2(int*, int*); //使用 typedef，函数类型
typedef int (*pFun2)(int*, int*); //使用 typedef，函数类型，函数指针
pFun2 pf2_2(int n){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}


//medthod3: 尾置返回类型
auto pf3(int n) -> int(*)(int *, int*){
    if(n>0)
        return &getMax;
    else
        return &getMin;
}

int main(){
    int i=-2, j=500;
    // test1
    cout << ">> method1" << endl;
    cout << pf1(1)(&i, &j) << endl;
    cout << pf1(-5)(&i, &j) << endl;
    // test2
    cout << ">> method2" << endl;
    cout << pf2(1)(&i, &j) << endl;
    cout << pf2(-5)(&i, &j) << endl;

    cout << pf2_(1)(&i, &j) << endl;
    cout << pf2_(-5)(&i, &j) << endl;
    
    cout << pf2_2(1)(&i, &j) << endl;
    cout << pf2_2(-5)(&i, &j) << endl;
    // test3
    cout << ">> method3" << endl;
    cout << pf3(1)(&i, &j) << endl;
    cout << pf3(-5)(&i, &j) << endl;

    return 0;
}