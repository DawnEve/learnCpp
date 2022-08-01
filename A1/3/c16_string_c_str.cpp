#include<iostream>
using namespace std;

// string 对象给 C风格字符串赋值
int main(){
    string s1="hello, world!";

    //char *s2=s1;
    // error: cannot convert ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’} to ‘c in initialization

    //char *s3=s1.c_str(); //error: invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]

    const char *s4=s1.c_str(); //一个指针，指向char的指针，指向的元素不能变更
    //s4[0] ='H'; //error: assignment of read-only location ‘* s4’
    
    //首字母大写
    s1[0]='H'; 
    cout << s4[0] << endl;
    cout << s4 << endl;

    // 指向第二个元素
    s4=&s1[1];
    cout << s4 << endl;

    // 如果改变了原始 string 字符串
    s1="ni hao";
    cout << s4 << endl;

    return 0;
}