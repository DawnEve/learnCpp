#include<iostream>
#include<string>
using namespace std;

int main(){
    string s1; //默认初始化，空字符
    string s2=s1; //s2 是s1的副本
    s1="c++";
    string s2_2(s1); //s2_2 是s1的副本，赋值后

    string s3="hello"; //s3是字面量值的副本
    string s3_2("hello"); //s3_2是字面量值的副本
    string s4(10, 'c'); // s4的值是10个字符c构成的字符串

    cout << "&s1=" << &s1 << ", s1=" << s1 << endl;
    cout << "&s2=" << &s2 << ", s2=" << s2 << endl;
    cout << "&s2_2=" << &s2_2 << ", s2_2=" << s2_2 << endl;
    cout << "&s3=" << &s3 << ", s3=" << s3 << endl;
    cout << "&s3_2=" << &s3_2 << ", s3_2=" << s3_2 << endl;
    cout << "&s4=" << &s4 << ", s4=" << s4 << endl;

    return 0;
}