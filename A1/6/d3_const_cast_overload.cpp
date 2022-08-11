#include<iostream>
using namespace std;

// 返回较短的字符串的引用
// 当实参不是const时，返回的结果仍然是const string 的引用
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}

int main(){
    string x1="hi", x2="hello";
    //string &y1=shorterString(x1, x2);// 返回的y1指向哪里?
    //error: binding reference of type ‘std::string&’ to ‘const string’
    string y1=shorterString(x1, x2); // 相当于复制

    const string &y2=shorterString(x1, x2); //返回的是引用，y2地址和x1一致：
    cout << "&x1=" << &x1 << endl;
    cout << "&y1=" << &y1 << endl; // 地址和x1不同
    cout << "&y2=" << &y2 << endl;

    y1="Hi"; //修改y1不影响原x1的值
    cout << "x1=" << x1 << endl;
    //y2="Hi"; // error: passing ‘const string’ 错误，不能使用const引用修改原值

    return 0;
}