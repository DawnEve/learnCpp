#include<iostream>
using namespace std;

//二义性调用
void f2(long){};
void f2(float){};


int main(){
    f2(3.14); //error: call of overloaded ‘f2(double) is ambiguous
    return 0;
}