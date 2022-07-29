#include<iostream>
using namespace std;

int main(){
    string s1="hello";
    unsigned n = -8; 

    cout << "s1=" << s1 << endl;
    cout << "n=" << n << endl;
    if(s1.size() < -8)
        cout << "s1.size < -8  is true " << endl;
    return 0;
}