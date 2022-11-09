#include<iostream>
using namespace std;

// replace 是调用 erase 和 insert 的一种简写形式
void demo1(){
    string s1="C++ book, 4th", s2=s1;
    cout << "s1.size()=" << s1.size() << endl;
    //把4th替换为 5th
    //方法1:
    s1.erase(10, 3);
    cout << "s1=" << s1 << endl;
    s1.insert(10, "5th");
    cout << "s1=" << s1 << endl;

    //方法2: 
    cout << "\ns2=" << s2 << endl;
    s2.replace(10, 2, "5th");
    cout << "s2=" << s2 << endl;
}

// 插入的可以和删除的不等长
void demo2(){
    string s1="c++ book, 4th";
    cout << "s1=" << s1 << endl;
    s1.replace(10, 2, "5th Edition");
    cout << "s1=" << s1 << endl; //c++ book, 5th Editionh
}

int main(){
    //demo1();
    demo2();

    return 0;
}