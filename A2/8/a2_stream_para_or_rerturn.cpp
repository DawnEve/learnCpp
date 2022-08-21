#include<iostream>
using namespace std;

// 流不能 拷贝 或 赋值，所以以 引用方式传递和返回流

// 引用方式传参
void read(istream &is, string &str){
    getline(is, str);
}

// 返回流：过滤掉字符,
istream &filter(istream &is){
    cout << "how to filter?" << endl;
    return is;
}

int main(){
    string s2="";
    // test1
    cout << "please input one line:" << endl;
    read(cin, s2);
    cout << "s2=" << s2 << endl;
    
    // test2
    read( filter(cin), s2 );
    cout << "s2=" << s2 << endl;

    return 0;
}