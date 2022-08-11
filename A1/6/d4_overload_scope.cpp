#include<iostream>
using namespace std;


//不同作用域无法重载函数

string read();
void print(const string &);
void print(double); //重载 print 函数

void fooBar(int ival){
    bool read=false; //内层作用域：隐藏了外层的read
    //string s=read(); //错误：read是一个布尔值，不是函数
    //error: ‘read’ cannot be used as a function

    //不好的习惯：在局部作用域声明函数
    void print(int); //新作用域：隐藏了之前的print，如果不声明，则最后一个 print(3.4) 输出 3.4；声明后则输出3

    //print("Value: "); //错误，外部的 print(const string &); 被隐藏掉了
    //error: invalid conversion from ‘const char*’ to ‘int’


    print(ival); //ok: 当前作用域 print(int) 可见
    print(3.14); //ok: 调用 print(int)，外部的 print(double) 被隐藏了
}

int main(){
    fooBar(5);
    return 0;
}


// 不能在函数内定义函数，不允许函数嵌套
// https://cplusplus.com/forum/beginner/199701/
void print(int x){
    cout << "int " << x << endl; 
}


void print(const string &x){
    cout << "const string &x=" << x << endl; 
}

void print(double x){
    cout << "double x=" << x << endl; 
}