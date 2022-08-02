#include<iostream>
using namespace std;

//const 用于参数传递
void reset(int *p){
    *p = 1;
}

void reset(int &r){
    r = 0;
}

void reset(string &r){
    r = "";
}

void reset2(const string &r){
    cout << "can not change " << r << endl;
}

int main(){
    int i=15;
    const int ci=i;
    string::size_type ctr=0;

    reset(&i); //调用形参类型是 int* 的reset 函数
    //reset(&ci); //错误，不能用指向 const int 的指针初始化 int *
    //error: no matching function for call to ‘reset(const int*)’

    reset(i); //调用形参类型是 int & 的reset 函数

    //reset(ci); //错误: 不能把普通引用绑定到 const 对象 ci 上
    // error: binding reference of type ‘int&’ to ‘const int’ discards qualifiers

    //reset(40); // 错误：不能把普通引用绑定到字面量(右值)上
    // error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’

    //reset(ctr); //错误，类型不匹配，ctr是无符号类型
    // error: no matching function for call to ‘reset(std::__cxx11::basic_string<char>::size_type&)’

    //reset("hello");     // error: invalid conversion from ‘const char*’ to ‘int’

    reset2("hello");     // reset2 的第一个形参是对常量的引用

    string s2="hi"; 
    reset(s2); //字符串对象的引用

    return 0;
}