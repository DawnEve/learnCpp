#include<iostream>
using namespace std;

// 默认实参
int increase(int x, int delta=1){
    return x+delta;
}

int main(){
    //调用
    int a=10;
    cout << increase(a) << endl;
    cout << increase(a, 1) << endl;
    cout << increase(a, 15) << endl;

    return 0;
}