#include<iostream>
using namespace std;

class NoDefault{
public:
    NoDefault(const std::string&);
    // 没有其他构造函数
};

struct A{             //默认情况下 my_mem 是 public 的
    NoDefault my_mem;
};

A a; //错误：不能为A合成构造函数
//error: use of deleted function ‘A::A()’ 这个错误一般是类A的默认初始化函数报错
//note: ‘A::A()’ is implicitly deleted because the default definition would be ill-formed

struct B{
    B(){}; //错误：b_member 没有值
    //error: no matching function for call to ‘NoDefault::NoDefault()’
    NoDefault b_member;
};

int main(){
    return 0;
}