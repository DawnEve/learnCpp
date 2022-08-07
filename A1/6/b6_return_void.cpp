#include<iostream>
using namespace std;

// 返回值是void的函数也可以使用 return expression; 只不过expression必须是返回void的函数。

void logs(int x){
    cout << "this is fn1(x), x=" << x << endl;
    return;
}

void fn(int a){
    return logs(a);
}

int main(){
    fn(500);
    return 0;
}