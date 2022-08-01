#include<iostream>
using namespace std;

//的两种形式 sizeof(type) 和 sizeof expr

struct Book{
    string bookNo="";
    int number=0;
    double price=0.0;
};

int main(){
    Book book1, *p;

    cout << sizeof(Book) << endl; //存储 Book 类型的对象所占的空间大小

    cout << sizeof(book1) << endl; // book1 的类型的大小，即 sizeof(Book)
    cout << sizeof *p << endl; //所指类型的大小

    cout << sizeof p << endl; // 8 指针所占空间大小
    cout << sizeof book1.number << endl; //4
    cout << sizeof Book::number << endl; //4

    return 0;
}