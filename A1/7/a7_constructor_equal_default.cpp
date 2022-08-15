#include<iostream>
using namespace std;

// = default; 表示默认构造函数
class A{
    int i=10;
    int j=5;
public:
    A(int x){ i=x;} //初始化 方法1
    A(int x, int y): i(x), j(y){} //初始化 方法2
    A() = default; //有其他构造函数，就必须有默认构造函数
    void info(){
        cout << "i=" << i << ", j=" << j << endl;
    }
};

int main(){
    A a1, a2(-6), a3(-1,1);
    a1.info();
    a2.info();
    a3.info();

    return 0;
}