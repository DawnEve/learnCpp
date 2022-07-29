#include<iostream>
using namespace std;

int main(){
    //1. typedef
    typedef int bookNumber; //bookNumber 是 int 的同义词。
    bookNumber book1=12;
    int book2=12;

    if(book1==book2)
        cout << "equal" << endl;

    //2. alias
    using int2=int; //int2 是 int 的别名
    int2 *p2=&book1;
    cout << "addr &book1=" << &book1 << ", p2=" << p2 << ", *p2="<< *p2 <<endl;

    return 0;
}