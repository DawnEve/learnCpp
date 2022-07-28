#include<iostream>
using namespace std;

// for 中定义的变量的作用范围: 循环体所在的花括号内。

int main(){
    int sum=0;
    int i=100;
    for(int i=0; i<=5;i++){
        sum+=i;
        cout << i << "\t" << sum << endl;
    }
    cout << "outside For: " << i << "\t" << sum << endl;
    return 0;
}