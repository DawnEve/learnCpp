#include<iostream>
using namespace std;

//2个类，X包含一个指向Y的指针，Y包含一个类型为X的对象
class X;
class Y;

class X{
    public:
    Y *py;
    int i=1;
};

class Y{
    public:
    X x;
    int j=20;
    X &get(){
        return this->x;
    }
};


int main(){
    X x1;
    Y y1;

    //y1.x = x1;
    y1.get() = x1;
    x1.py = &y1;


    cout << x1.py->x.i << endl;

    cout << "&x1:\t" << &x1 << endl;
    cout << "&y1:\t" << &y1 << endl << endl;
    //
    cout << "x1.py:\t" << x1.py << endl;
    cout << "&(y1.x):" << &(y1.x) << endl;
    cout << "y1.get():" << &(y1.get()) << endl;

    return 0;
}