#include<iostream>
using namespace std;

int main(){
    string hexSymbols="0123456789ABCDEF";
    cout << "Please enter some numbers between 0-15, and get their hex:" << endl;

    string result; //保存16进制结果
    string::size_type n; //保存用户输入的数

    while(cin >> n){
        if(n<hexSymbols.size()){ //忽略无效输入
            result += hexSymbols[n];
        }
    }
    cout << "Your hex is:" << result << endl;
    return 0;
}