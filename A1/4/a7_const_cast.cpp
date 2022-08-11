#include<iostream>
using namespace std;

// const_cast 只能改变运算对象的低层const
int main(){
    char s1='c', s2='x';
    const char *cp = &s1; //从右向左读：cp是一个指针；指向一个char类型；指向的char值是常量
    //修改
    s1='b';
    
    //*cp='a'; //底层const，指向的值只读，不能通过该指针写其指向的值。
    //error: assignment of read-only location ‘* cp’ 
    cp=&s2; //但可以修改该指针中的地址
    //*cp='y'; //只读，通过指针不能修改其指向的值
    
    cout << "1 " << s1 << endl;
    cout << "2 " << *cp << endl;

    //修改指针类型，看能否只读变读写
    char *p = const_cast<char *>(cp); //正确，但是通过p写值是未定义的行为？//todo 什么叫未定义的行为？
    cout << "3 cp:" << (void *)cp  << ", p:" << (void *)p << endl; //强转后，指针中保存的地址不变
    // 打印字符的地址，见上一个示例: a6

    cout << "4 " << *p << endl;

    //修改值
    *p='z';
    cout << "5 " << *p << endl;
    cout << "6 " << s2 << endl;

    return 0;
}