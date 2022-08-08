#include<iostream>
using namespace std;

//显示递归函数中的变量的地址
void showAddr(int n){
    cout << "Before " << n << ", addr:" << &n << endl;
    if(n<4)
        showAddr(n+1);
    cout << " After " << n << ", addr:" << &n << endl;
}

int main(){
    showAddr(0);
    return 0;
}