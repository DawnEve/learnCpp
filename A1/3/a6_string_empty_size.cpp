#include<iostream>
using namespace std;

int main(){
    string s1="";
    string s2("hello world");

    if( !s1.empty() )
        cout << "s1 size:" << s1.size() << endl;
    else 
        cout << "s1 is empty" << endl;
    
    if( !s2.empty() )
        cout << "s2 size:" << s2.size() << endl;
    return 0;
}