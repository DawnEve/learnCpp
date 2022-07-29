#include<iostream>
using namespace std;

int main(){
    string s1="hello", s2="world";
    string s3=s1+" "+s2;

    //string s4="hello" + " world";
    //error: invalid operands of types ‘const char [6]’ and ‘const char [7]’ to binary ‘operator+’

    string s5="hello" + string(" world");
    cout << s5 << endl;

    return 0;
}