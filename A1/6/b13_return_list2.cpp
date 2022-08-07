#include<iostream>
using namespace std;

//返回内置类型的 列表初始化值
int init(int x){
    //return {x, 100}; //error: cannot convert ‘<brace-enclosed initializer list>’ to ‘i in return
    return {x};
}

int main(){
    int a=init(10);
    cout << a << endl;
    return 0;
}