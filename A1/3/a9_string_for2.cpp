#include<iostream>
using namespace std;

int main(){
    string s1="hello, world!";

    for(char s : s1){
        s = toupper(s); //not work
    }
    cout << s1 << endl;

    //需要使用引用
    for(char &ref : s1){ //ref 是 上文 s 的引用，同名
        ref = toupper(ref);
    }
    cout << s1 << endl;

    return 0;
}