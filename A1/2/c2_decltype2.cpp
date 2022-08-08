#include<iostream>
using namespace std;

// 变量，加括号的变量，得到的类型是不同的
int main(){
    int i=10;

    decltype(i) d; //正确，d是一个未初始化的 int
    //decltype((i)) e; //错误，e是一个int&，必须初始化
    //error: ‘e declared as reference but not initialized

    int num=10;
    decltype((i)) e=num; //绑定变量
    e=200;
    cout << num << endl;

    return 0;
}