#include<iostream>
int main(){
    const int buf_size=1024;
    const int &ref=buf_size; //正确，引用及其对应的对象都是常量

    //int &ref2=buf_size; //错误，引用不是常量
    //error: binding reference of type ‘int&’ to ‘const i discards qualifiers

    //ref=512; //错误，引用就是别名，常量不能修改。
    // error: assignment of read-only reference ‘ref’
    
    return 0;
}