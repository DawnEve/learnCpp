#include<iostream>
#include<string>
using namespace std;

//lambda的捕获列表
void demo1(){
    string::size_type sz=4;
    //lambda定义在函数内，则可以使用函数的局部变量，但是需要放到捕获组中
    auto f=[sz](const string &s){ 
        return s.size() > sz;
    };
    cout << f("hello world") << endl;
    cout << f("hi") << endl;
}

void demo2(){
    string::size_type sz=4;
    //不放到捕获组中，则报错
    auto f=[](const string &s){ 
        //return s.size() > sz; // 编译失败 error: ‘sz’ is not captured
        return s.size();
    };
    cout << f("hello world") << endl;
    //cout << f("hi") << endl;
}

int main(){
    demo1();
    //demo2();

    return 0;
}