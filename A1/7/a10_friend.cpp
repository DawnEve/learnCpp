#include<iostream>
using namespace std;

// 友元：能访问类私有成员的函数
class A{
private: //对友元没影响
    friend void add(A &, int); //添加友元声明，就可以访问私有成员i了
    int i=0;
public:
    void show(){
        cout << i << endl;
    }
};

void add(A &a, int x){
    a.i += x;  //只有友元函数、类内成员函数才可以访问私有成员
}

int main(){
    A a1;
    add(a1, 25);
    a1.show();

    return 0;
}