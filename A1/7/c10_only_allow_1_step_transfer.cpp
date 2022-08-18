#include<iostream>
using namespace std;

//编译器只能进行一步类型转换，需要两步时报错
class Book{
    string ISBN;
public:
    //提供可用的构造函数
    Book(string s=""): ISBN(s) {}
    //其他方法
    string isbn(){return ISBN;}
    Book &combine(const Book &book){
        ISBN += book.ISBN;
        return *this;
    }
};

int main(){
    string s1="9-99";
    Book book;
    cout << "1 " << book.isbn() << endl;
    book.combine(s1);
    cout << "2 " << book.isbn() << endl;
    
    //book.combine("-12-34"); //error: cannot convert ‘const char [6]’ to ‘const Book&’
    // 字符字面量本质上是字符数组，第一步转为string类，第二步通过Book()构造函数转为Book类。
    
    book.combine( string("-12-34") ); //显式转为 string，隐式转为Book
    book.combine( Book("-56-78") ); //隐式转为string，显示转为 Book
    cout << "3 " << book.isbn() << endl;
    return 0;
}