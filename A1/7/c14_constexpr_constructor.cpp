#include<iostream>
using namespace std;

// constexpr 构造函数：一般应该是空的
class Debug{
public:
    constexpr Debug(bool b=true): hw(b), io(b), other(b){}
    constexpr Debug(bool h, bool i, bool o):hw(h), io(i), other(o) {}
    constexpr bool any() const { return hw || io || other;}
    void set_io(bool b){io=b;}
    void set_hw(bool b){hw=b;}
    void set_other(bool b){other=b;}
private:
    bool hw; //硬件错误，而非IO错误
    bool io; //IO错误
    bool other; //其他错误
};

int main(){
    //test1
    constexpr Debug io_sub(false, true, false); //调试io
    if(io_sub.any())  //等价于 if(true)
        cerr << "print appropriate error messages" << endl;
    //test2
    constexpr Debug prod(false); //无调试
    if(prod.any()) //等价于 if(false)
        cerr << "print an error message" << endl;
    return 0;
}