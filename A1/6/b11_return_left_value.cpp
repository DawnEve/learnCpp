#include<iostream>
using namespace std;

//为返回左值的函数结果赋值，不能是常量
char &get_val(string &str, string::size_type index){
    return str[index];
}


int main(){
    string s1="hello";
    cout << "1 &s1=" << &s1 << endl;

    string &s2=s1;
    cout << "2 &s2=" << &s2 << endl; //引用，就是别名，所以指向的地址是相同的。


    // 无法获取返回的引用的地址 //todo why?
    cout << "3 get_val(s1, 0): " << get_val(s1, 0) << endl;
    cout << "4 &get_val(s1, 0): " << &get_val(s1, 0) << endl;
    //赋值给变量也不行 //todo why?
    char &r1=get_val(s1, 0); // 加const也不报错
    cout << "5 r1=" << r1 << endl; //拿不到地址
    cout << "6 &r1=" << &r1 << endl;
    //通过修改r1修改s1的值
    r1='a';
    cout << "7 s1=" << s1 << endl;

    //通过左值改变原始字符串
    cout << "8 s1=" << s1 << endl;
    get_val(s1, 0)='H'; //将 s1[0] 的值改为H
    cout << "9 s1=" << s1 << endl;

    return 0;
}