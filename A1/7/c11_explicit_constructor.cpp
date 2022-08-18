#include<iostream>
using namespace std;

// 阻止隐式类型转换

class Sales_data{
private:
    std::string bookNo;
    unsigned units_sold;
    double revenue;
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) {}
    explicit  //加上这个符号，就不能string to Sales_data 隐式转换了
    Sales_data(const std::string &s): bookNo(s) {}
    explicit Sales_data(std::istream &);
    //其他不变 
    void show(){ cout << bookNo << endl;}
};

int main(){
    Sales_data sd;
    //sd=string("IS-99-9"); //error: no match for ‘operator=’ (operand types are ‘Sales_data’ and ‘std::string’
    sd=Sales_data("IS-99-8");

    sd.show();

    return 0;
}
