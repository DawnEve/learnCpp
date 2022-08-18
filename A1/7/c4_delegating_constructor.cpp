#include<iostream>
using namespace std;

//委托构造函数

class Sales_data{
private:
    std::string bookNo;
    unsigned units_sold;
    double revenue;
public:
    //非委托构造函数使用对应的实参初始化成员
    Sales_data(std::string s, unsigned cnt, double price):
        bookNo(s), units_sold(cnt), revenue(cnt * price) {}
    //其余构造函数全部委托给零一个构造函数
    Sales_data(): Sales_data("", 0, 0){}
    Sales_data(std::string s): Sales_data(s, 0, 0) {}
    //Sales_data(std::istream &is):Sales_data() { read(is, *this);}

    //其他函数
    void print(){
        cout << bookNo << "\t" << units_sold << "\t" << revenue << endl;
    };
};

int main(){
    Sales_data sd1("S1", 1, 1), sd2, sd3("s3");
    sd1.print();
    sd2.print();
    sd3.print();
    return 0;
}