#include<iostream>
using namespace std;

// 计算 1+2+3+...+100
int main(){
    int sum=0, i=0;
    while (i<=100){
        sum+=i;
        i++;
    }
    cout << "sum of 1+2+...+100=" << sum << endl;
    return 0;
}