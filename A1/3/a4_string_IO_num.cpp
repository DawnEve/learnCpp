#include<iostream>
using namespace std;

int main(){
    string word;
    cout << "Please input several string(s):" << endl;
    int i=0;
    while(cin >> word){
        i++;
        cout << i << ">>" << word << endl;
    }
    return 0;
}