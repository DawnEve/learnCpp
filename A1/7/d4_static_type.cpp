#include<iostream>
using namespace std;

// 
class Bar{
public:
    Bar(int i=0): x(i) {}
    void show(){ cout << x << endl;}
private:
    int x;
    static Bar mem1; //正确：静态成员可以是不完全类型
    Bar *pmem2; //正确：指针成员可以是不完全类型
    //Bar mem3; //错误：数据成员必须是完全类型
    // error: field ‘mem3’ has incomplete type ‘Bar’
};

int main(){
    Bar b1;
    b1.show();
    return 0;
}