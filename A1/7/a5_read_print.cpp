#include<iostream>
using namespace std;

struct Sales_data{
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;

    std::string isbn() const { return bookNo;} //必须加const：print函数的形参要求
    double avg_price() const;
};
double Sales_data::avg_price() const {
    if(units_sold)
        return revenue / units_sold;
    else 
        return 0;
}

//接口成员，但不是类成员
istream &read(istream &is, Sales_data &item){
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
ostream &print(ostream &os, const Sales_data &item){
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}

int main(){
    Sales_data sd1, sd2;
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd1); //输入
    print(cout, sd1) << endl; //输出
    print(cout, sd2) << endl; //输出
    return 0;
}