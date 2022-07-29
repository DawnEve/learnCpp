#include<iostream>
using namespace std;

int main(){
    string s1="hi, c++";
    cout << s1 << endl;

    for(int i=0; i<s1.size(); i++){
        if(i==0)
            s1[i]=toupper(s1[i]); //首字母大写
        cout << i << "\t" << s1[i] << endl;
    }
    cout << s1 << endl;
    return 0;
}