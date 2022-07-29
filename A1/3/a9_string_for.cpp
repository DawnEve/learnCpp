#include<iostream>
using namespace std;

int main(){
    string s1="hello";

    for(char s : s1){ //auto s
        cout << s << endl;
    }
    return 0;
}