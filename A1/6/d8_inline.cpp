#include<iostream>
using namespace std;

// 内联函数
inline const string &
shorterString(const string &s1, const string &s2){
    return s1.size() < s2.size() ? s1 : s2;
}

int main(){
    string x1="hi", x2="hello";
    cout << shorterString(x1, x2) << endl;

    return 0;
}