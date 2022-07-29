#include<iostream>
using namespace std;

int main(){
    double pi=3.14;
    double pi2=3.1415926;
    const double *cptr;
    cptr=&pi;
    cout << "cptr=" << cptr << ", *cptr=" << *cptr << endl;

    cptr=&pi2; //也就是说const修饰的指针变量是可以修改的
    cout << "cptr=" << cptr << ", *cptr=" << *cptr << endl;

    //*cptr=10.2; //但是不能通过指针修改其所指的对象的值
    //error: assignment of read-only location ‘* cptr’

    return 0;
}