#include<iostream>
using namespace std;

//i和j都必须定义在函数体之外
int j=0; //定义在函数内则报错: error: ‘& i’ is not a constant expression
constexpr int i=1024; // i的类型为 整形常量

int main(){
    constexpr int *np=nullptr; //np是一个指向整数的常量指针，其值为空

    constexpr const int *p= &i; //p 是常量指针，指向 整形常量i
    constexpr int *p2=&j; //p2 是常量指针，指向 整数j

    return 0;
}