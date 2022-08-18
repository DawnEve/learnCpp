#include<iostream>
using namespace std;

//委托构造函数，如果函数体不为空，执行顺序？

class Sales_data{
private:
    std::string bookNo;
    unsigned units_sold;
    double revenue;
public:
    //非委托构造函数使用对应的实参初始化成员
    Sales_data(std::string s, unsigned cnt, double price):
        bookNo(s), units_sold(cnt), revenue(cnt * price) {
            cout << "c1-first: B " << units_sold << endl;
            units_sold =10;
            cout << "c1-first: A" << units_sold << endl;
    }
    //其余构造函数全部委托给零一个构造函数
    Sales_data(std::string s=""): Sales_data(s, 5, 0){
        cout << "C2: B" << units_sold << endl;
        units_sold =20;
        cout << "C2: A" << units_sold << endl;
    }

    //其他函数
    void print(){
        cout << bookNo << "\t" << units_sold << "\t" << revenue << endl;
    };
};

int main(){
    Sales_data sd1("Sd1"); 
    //先执行初始化列表 - 执行权跑到调用的构造函数 - 初始化列表： 5
    // 然后是该函数的函数体：10
    // 然后调用结束，回到调用函数，执行函数体: 20
    // 构造函数 执行结束。
    sd1.print();
    return 0;
}