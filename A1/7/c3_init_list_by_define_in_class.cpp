#include<iostream>
using namespace std;

// 构造函数初始值列表不影响初始化顺序，决定性的是这些成员在类中定义的先后

class X{
public:
    int i;
    int j;
    // 未定义的： i在j之前被初始化。
    // 所以i是一个随机j值，然后j是val
    X(int val): j(val), i(j){}
};


int main(){
    X x(2);
    cout << "x.i=" << x.i << endl;
    cout << "x.j=" << x.j << endl;
    return 0;
}