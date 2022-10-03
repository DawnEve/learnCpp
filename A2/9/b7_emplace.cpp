#include<iostream>
#include<list>
using namespace std;

// emplace 的使用

struct Sales_data{
    string ISBN;
    int number;
    double price;

    Sales_data()=default;
    Sales_data(string isbn, int num, double p): ISBN(isbn), number(num), price(p){
        cout << ">> 2 S_d(double)" << endl;
    };
    void show(){
        cout << "Class Sales_data: ISBN:" << ISBN << ", number:" 
             << number << ", price:" << price << endl;
    }
};

int main(){
    Sales_data c1("I4", 2, 10), c2={"I2", 10, 5}, c3;
    cout << c1.price << endl;
    cout << c2.price << endl;
    cout << c3.price << endl; //走默认构造函数，没有初始化，是内存中原来的值。比如 2.12203e-314

    // 在c的末尾构造一个 S_d 对象
    list<Sales_data> c;
    // 使用3个参数的 Sales_data 构造函数
    c.emplace_back("978-05", 25, 15.99);
    // 错误：没有接收3个参数的 push_back 版本
    //c.push_back("978-05", 25, 15.99); //error: no matching function for call to
    //正确，创建一个临时的 Sd对象传递给 push_back
    c.push_back( Sales_data("978-05", 25, 16.00) );

    // 打印
    for(auto i: c)
        i.show();   

    return 0;
}