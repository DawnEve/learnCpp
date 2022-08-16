#include<iostream>
using namespace std;

//可变成员，甚至可以被const函数修改
class Screen{
public:
    void some_member() const;
    void show(){ cout << access_ctr << endl;}
    void show2(){ cout << access_ctr2 << endl;}
private:
    mutable size_t access_ctr=0; //即使一个const 对象内也能被修改
    size_t access_ctr2=0; //没有 mutable 前缀
};

void Screen::some_member() const{
    ++access_ctr; //保存一个计数器，用于记录函数被调用次数
    //++access_ctr2; //error: increment of member ‘Screen::access_ctr2’ in read-only object
}

int main(){
    Screen sc1;
    sc1.some_member();
    sc1.some_member();
    sc1.show();
    sc1.show2();

    return 0;
}