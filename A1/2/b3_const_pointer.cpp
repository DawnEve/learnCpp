#include<iostream>
using namespace std;

int main(){
    const double pi=3.1415;

    //存放常量对象的地址，需要指向常量的指针
    //double *ptr=&pi; //错误：ptr是一个普通指针
    // error: invalid conversion from ‘const double*’ to ‘double*’ [-fpermissive]

    const double *cptr=&pi; //正确，cptr是一个指向双精度常量的指针
    //*cptr=10; //错误，不能给 const 修饰的常量赋值
    //error: assignment of read-only location ‘* cptr’

    cout << "cptr=" <<cptr << ", *cptr=" << *cptr << endl;

    return 0;
}