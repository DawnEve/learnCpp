#include<iostream>
using namespace std;

int add(int x, int y){
    int b;
    cout << "para in function, not init: " << b << endl;
    return x+y;
}

int main(){
    int a;
    cout << a << endl; //0
    cout << add(1,5) << endl; //不确定函数内的b的值
    return 0;
}