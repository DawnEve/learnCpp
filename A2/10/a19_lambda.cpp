#include<iostream>
using namespace std;

int main(){
    // 定义 lambda 表达式
    auto f=[]{return 10;};
    // 调用
    cout << f() << endl;
}