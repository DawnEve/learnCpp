#include<iostream>
using namespace std;

int main(){
    string line;
    cout << "Please input several string(s):" << endl;
    while( getline(cin, line) ){
        cout << "Your input is: " << line << endl;
    }
    return 0;
}