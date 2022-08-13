#include<iostream>
using namespace std;

//返回引用的函数作为左值

class A{
    int number;
    public:
    A(int x){number=x;}
    int getN() const { return number;}

    A &bigger(A &rhs){ //也可传入指针
        return number > rhs.getN()? *this: rhs;    
    }
};

int main(){
    A a1(1), a2(20);
    // 函数作为左值，因为函数返回的是引用
    a1.bigger(a2) = 5000; //把大的值修改为5000。等号左侧是一个对类的引用，怎么赋值的？
    a1=10; //这又是什么语法？？？竟然可以赋值成功

    cout << "a1=" << a1.getN() << endl;
    cout << "a2=" << a2.getN() << endl;
    
    return 0;
}