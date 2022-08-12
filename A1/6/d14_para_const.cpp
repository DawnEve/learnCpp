#include<iostream>
using namespace std;

//形参有const的引用或指针
void f3(int &){ cout << "int &" << endl;} //函数的参数是 int 的引用
void f3(const int &){ cout << "const int &" << endl;} //函数的参数是一个常量引用
const int a=10;
int b=20;

int main(){
    f3(a); //调用 f3(const int &)
    f3(b); //调用 f3(int &)

    return 0;
}