#include<iostream>
using namespace std;

// 怎么使用 默认构造函数？
struct Sales_data{
    string ISBN="IS";
    string isbn(){ return ISBN;}
    string show(){
        return isbn();
    }
};

Sales_data obj(); //正确，声明了一个函数而非对象
Sales_data obj2; //正确，obj2是一个对象

int main(){
    cout << &obj << endl;
    cout << &obj2 << endl;

    cout << obj << endl;
    cout << obj().show() << endl;
/*
    if ( obj.isbn() == obj2.isbn() ){  //错误：obj 是一个函数
    // error: request for member ‘isbn’ in ‘obj’, which is of non-class type ‘Sales_data()’
        cout << "eq" << endl;
    }
*/

    return 0;
}

Sales_data obj(){ //定义该函数
    return obj2;
}