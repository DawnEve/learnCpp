#include<iostream>
#include<vector>
using namespace std;

class Book{
    int i;
public:
    Book(int x): i(x){} //没有默认构造函数

    void print() const { //这个const 是修饰传入函数的 this 的
        cout << "Class Book: i="<< i << endl;
    }
};

int main(){
    //vector<Book> vb0(10); //error: no matching function for call to ‘Book::Book()’
    vector<Book> vb1(10, 1); //这里调用了默认类型转换，int to Book，通过构造函数实现
    for(auto be=vb1.cbegin(); be < vb1.cend(); be++){
        //(*be).print();
        be->print(); //迭代器就是针用
    }


    return 0;
}