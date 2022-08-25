#include<iostream>
#include <fstream> 
using namespace std;

class Sales_data{
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
public:
    Sales_data() = default;
    Sales_data(std::istream &);
    std::string isbn() const { return bookNo;}
    Sales_data &combine(const Sales_data &);
private:
    double avg_price() const;
    string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};

/********** 声明部分 ************/
std::istream &read(std::istream&, Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);


/********** 定义部分 ************/
// 类外的构造函数，定义
Sales_data::Sales_data(std::istream &is){
    read(is, *this); //read函数的作用：从is中读取一条交易信息，存入this对象中
}

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


// 成员函数的定义
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



// 读文件
int main(int argc, char *argv[]){
     Sales_data sd1, sd2;
    /*
    // 测试IO
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd1); //输入

    print(cout, sd1) << endl; //输出
    */

    ifstream input(argv[1]); //打开输入文件
    ofstream output(argv[2]); //打开输出文件
    Sales_data total;
    if( read(input, total) ){
        Sales_data trans; //保存下一条记录
        while( read(input, trans)){
            if(total.isbn() == trans.isbn()){
                total.combine(trans);
            }else{
                print( output, total) << endl; //打印结果
                total = trans; //处理下一本
            }
        }
        print(output, total) << endl; //打印最后一本书的销售额
    }else 
        cerr << "No data?!" << endl;
    return 0;
}

/*
$ cat a8_out.txt
S1 4 80.4 20.1
S2 1 30.5 30.5

$ g++ a8_read_file.cpp
$ ./a.out a8_file.txt a8_out.txt

$ cat a8_out.txt 
S1 4 80.4 20.1
S2 1 30.5 30.5
*/
