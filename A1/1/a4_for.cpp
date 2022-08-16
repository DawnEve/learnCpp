#include<iostream>
using namespace std;

// 计算 1+2+3+...+100
int main(){
    int sum=0;
    for(int i=0; i<=100; i++){
        sum+=i;
    }
    cout << "(for)sum of 1+2+...+100=" << sum << endl;
    return 0;
}

