#include<iostream>
using namespace std;

// 阶乘函数
int fact(int n){
    int rs=n;
    while( --n > 0){
        rs *= n;
    }
    return rs;
}
int main(){
    int i;
    cout << "please input an int:" << endl;
    cin >> i;
    cout << i << "!=" << fact(i) << endl;

    return 0;
}