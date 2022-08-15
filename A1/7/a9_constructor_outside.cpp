#include<iostream>
using namespace std;

//类外定义构造函数：一个依赖输入的构造函数
class A{
    int i;
public:
    A()=default;
    A(istream &); //构造函数，声明
    void show(){
        cout << "i=" << i << endl;
    }
};

//构造函数，定义
A::A(istream &is){
    cout << "Please input the init value of i in class A: " << endl;
    is >> i;
}

int main(){
    A a1(cin);
    a1.show();

    return 0;
}