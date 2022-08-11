#include<iostream>
using namespace std;

// 返回较短的字符串的引用
// 当实参不是const时，返回的结果仍然是const string 的引用
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
}

//重构一个：当实参不是常量时，得到的结果也是一个普通的引用
string &shorterString(string &s1, string &s2){
    auto &r=shorterString( const_cast<const string&>(s1), 
                           const_cast<const string&>(s2) );
    return const_cast<string&>(r);
}

int main(){
    string x1="hi", x2="hello";

    //2. 当输入不是常量时，返回的也不是常量
    string &y1=shorterString(x1, x2); //只有第一个函数时报错，加重载函数后就对了
    cout << y1 << endl;

    //查看地址
    cout << "&x1: " << &x1 << endl;
    cout << "&y1: " << &y1 << endl;

    //那就可以修改值
    y1="Hi!";
    cout << x1 << endl;

    return 0;
}
