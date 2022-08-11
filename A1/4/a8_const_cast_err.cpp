#include<iostream>
using namespace std;

// const_cast 只能改变 const 属性，不能改其他类型。
int main(){
    char s1= 'c', *ps1=&s1;
    const char *cp = &s1;

    //char *q = static_cast<char*>(cp); // error: invalid static_cast from type ‘const char*’ to type ‘char*’
    char *q = const_cast<char*>(cp);
    cout << *q << endl;

    // 转为字符串类型
    string s2= static_cast<string>(cp); //正确：字符串字面值转换成string类型
    cout << s2 << endl;

    //string s3= const_cast<string>(cp); //错误: const_cast 只能修改const属性
    char *p3= const_cast<char*>(cp);
    *p3='d';
    cout << *q << endl;

    return 0;
}