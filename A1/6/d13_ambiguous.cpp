#include<iostream>
using namespace std;

//二义性调用
void f();
void f(int);
void f(int, int);
void f(double, double=3.14);

int main(){
    f(12, 2.5); //error: call of overloaded ‘f(int, double) is ambiguous
    return 0;
}

void f(int, int){
    cout << "int" << endl;
}
void f(double, double){
    cout << "double" << endl;
}
