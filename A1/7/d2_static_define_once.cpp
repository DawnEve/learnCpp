#include<iostream>
using namespace std;

// 静态数据成员只能定义一次
class Book{
public:
    Book(string isbn=""): ISBN(isbn){}
    void show(){ cout << ISBN << ", " << total << endl; }
    static int total;
private:
    string ISBN;
};

//必须定义在全局作用域：定义在main内报错。
int Book::total =100; //定义

int main(){
    Book book("IS-9-99"), *pb = &book;
    Book::total =12; //修改静态成员的值：只用类名
    pb->total = 125; //使用指针修改
    book.total=25; //使用对象名修改
    book.show();

    return 0;
}