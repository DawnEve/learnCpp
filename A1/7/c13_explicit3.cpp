#include<iostream>
using namespace std;

//显式调用加 explicit的构造函数
class Sales_data{
public:
    explicit Sales_data(string s1): bookNo(s1){}
    Sales_data &combine(const Sales_data &item){
        bookNo += item.bookNo;
        return *this;
    }
    void show(){ cout << bookNo << endl;}
private:
    string bookNo;
};

int main(){
    Sales_data sd1("IS1-1");
    sd1.show();

    string null_book="-1-23";
    //sd1.combine( null_book ); //构造函数加 explicit 后就不能隐式转换了
    sd1.combine( Sales_data(null_book) ); // 显式构造的 Sales_data对象
    sd1.combine( static_cast<Sales_data>(null_book) ); // 显式转换，也可以
    // static_cast 可以使用 explicit 的构造函数
    sd1.show();
    return 0;
}