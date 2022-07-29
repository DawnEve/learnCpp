#include<iostream>
using namespace std;
int main(){
    double pi = 3.14; 
    double *const cpi= &pi; //看这个定义，从右向左阅读
    // 距离 cpi 最近的是 const，意味着 cpi 本身是常量，不能修改
    // 接着是 * 表示 cpi 是一个指针
    // 最后是 double 表示指针指向的是一个double变量，可以通过指针修改

    const double *const cpi2=&pi;
    //从右向左，这个最后的修饰符是一个 const，表示指针指向的也是一个常量，也不能通过指针修改。


    cout << "pi=" << pi << ", addr &pi=" << &pi << endl;
    cout << "1 cpi=" << cpi << ", value *cpi=" << *cpi << endl;
    
    //可以通过指针修改值
    *cpi=3.1415926;
    cout << "2 cpi=" << cpi << ", value *cpi=" << *cpi << endl;

    //不能修改指针中保存的地址
    double piLong=3.14159265358979;
    //cpi=&piLong; //指针变量中保存的地址 只读
    // error: assignment of read-only variable ‘cpi’

    //对于 cpi2则指针变量中的地址是常量，指针指向的对象也是常量
    //cpi2=&piLong; //error: assignment of read-only variable ‘cpi2’
    //*cpi2=3.1; //error: assignment of read-only location ‘*(const double*)cpi2’

    return 0;
}