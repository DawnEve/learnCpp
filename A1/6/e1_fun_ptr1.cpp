#include<iostream>
using namespace std;

//获取函数的指针
// 比较2个string对象的长度
bool lengthCompare(const string &s1, const string &s2){
    return s1.size() > s2.size();
}

// pf指向一个函数，该函数的返回值是 bool 类型，形参是 2个 const string 的引用
bool (*pf)(const string &, const string &); //未初始化
bool (*pf2)(const string &, const string &) = &lengthCompare; //初始化

int main(){
    cout << (void *)lengthCompare << endl;
    pf = lengthCompare;
    //pf2= &lengthCompare; //取地址符是可选的
    cout << (void *)pf << endl;
    cout << (void *)pf2 << endl;

    //2. 使用函数指针，无需提前解引用
    bool b1=lengthCompare("hi", "hello"); //直接使用函数名
    bool b2= (*pf)("hi", "hello"); //解引用
    bool b3= pf("hi", "hello"); //不解引用，也可以
    cout << "b1=" << b1 << endl;
    cout << "b2=" << b2 << endl;
    cout << "b3=" << b3 << endl;

    return 0;
}