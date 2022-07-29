#include<iostream>
using namespace std;

//没有加 #include<string> 也没报错?

int main(){
    string s1, s2, s3;
    cout << "Pleae input 3 strings, separate by blank" << endl;
    cin >> s1 >> s2 >> s3;

    cout << "value of s1=" << s1 << endl;
    cout << "value of s2=" << s2 << endl;
    cout << "value of s3=" << s3 << endl;
    return 0;
}