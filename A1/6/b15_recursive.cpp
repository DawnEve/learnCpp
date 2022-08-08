#include<iostream>
using namespace std;

// 递归求阶乘
long fact(int n){
    long result=1;
    if(n<=1)
        return 1;
    return n*fact(n-1);
}

int main(){
    int i=5;
    cout << i << "!=" << fact(i) << endl;

    return 0;
}