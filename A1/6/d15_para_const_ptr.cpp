#include<iostream>
using namespace std;

//形参有const的常量或指针
void f4(int *){ cout << "int *" << endl;} //函数的参数是指向 int 的指针
void f4(const int *){ cout << "const int *" << endl;} //函数的参数是一个指向 常量int 的指针

int a=10, b=20;
const int *pa=&a;
int *pb=&b;

int main(){
    f4(pa); //调用 f4(const int *)
    f4(pb); //调用 f4(int *)

    return 0;
}
