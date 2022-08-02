#include<iostream>
#include<string>
using namespace std;

//比较长字符串的长度的函数
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

int main(){
    string str1="hi";
    string str2="hello!";

    cout << str1 << " is shorter than " << str2 << "?" << endl;

    string result = isShorter(str1, str2)==1 ? "yes": "no";
    cout << result << endl;
    return 0;
}