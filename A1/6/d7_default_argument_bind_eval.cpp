#include<iostream>
using namespace std;

// 默认实参是变量时，绑定是函数声明所在的环境，求值是函数调用所在的环境

//函数声明
int width=80;
int height=200;
char ch='#';
void screen(int w=width, int h=height, char ch=ch){
    cout << ">> w=" << w << ", h=" << h << ", ch=" << ch << endl;
}

void fn(){
    screen();
    //修改调用环境
    width=8; //更新了外部变量width
    int height=5; // 隐藏了外部变量，这个内部变量与screen函数默认实参没有关系了。
    //height=500; //看声明和定义谁先出现，
    //如果对height赋值先出现，则认为是外部变量；如果声明先出现，认为是局部新变量。

    screen();
}

int main(){
    fn();
    return 0;
}

