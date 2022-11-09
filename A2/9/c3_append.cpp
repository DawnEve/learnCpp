#include<iostream>
using namespace std;

// append: 在string末尾插入
void demo1(){
    string s1("C++ book"), s2=s1;
    s1.insert(s1.size(), " 5th edition");; //在末尾插入
    s2.append(" 5th Edi");//简写
    cout << "s1=" << s1 << endl;
    cout << "s2=" << s2 << endl;
}

int main(){
    demo1();

    return 0;
}