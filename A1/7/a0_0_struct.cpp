#include<iostream>
using namespace std;

// Sales_data 类 v1
struct Sales_data{

    //构造函数
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s){}
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(std::istream &);

    //新成员：对于 Sales_data 对象的操作
    std::string isbn() const { return bookNo;}
    Sales_data &combine(const Sales_data &);

    double avg_price() const; //最后的const 啥意思？
    // 数据成员和 P64 相同
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};

//Sales_data 的非成员接口函数 声明放前面
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

/******************* 函数(构造函数)的定义 ********************/

//类外的构造函数，定义
Sales_data::Sales_data(std::istream &is){
    read(is, *this); //read函数的作用：从is中读取一条交易信息，存入this对象中
}

// 非成员函数的定义
double Sales_data::avg_price() const {
    if(units_sold)
        return revenue / units_sold;
    else 
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold; //把rhs的成员加到this对象的成员上
    revenue += rhs.revenue;
    return *this; //返回调用该函数的对象
}

// 接口函数，但不是类成员

// 输入的交易信息：ISBN、售出总数和售出价格
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

Sales_data add(const Sales_data &lhs, const Sales_data &rhs){
    Sales_data sum = lhs; //把lhs 的数据成员拷贝给sum
    sum.combine(rhs); //把rhs的数据成员加到sum当中
    return sum;
}


/**
 * @brief 测试每一个构造函数
 * 
 * @return int 
 */

int main(){
    Sales_data sd1, sd2;
    // 测试IO
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd1); //输入
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd2); //输入
    print(cout, sd1) << endl; //输出
    print(cout, sd2) << endl; //输出

    // 合并
    sd1.combine(sd2);
    print(cout, sd1) << endl; //输出
    
    return 0;
}