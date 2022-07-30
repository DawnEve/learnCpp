#include<iostream>
using namespace std;

//第一个单词大写
int main(){
    string s2="hello world!";
    for(auto it=s2.begin();  it != s2.end() && !isspace(*it);  ++it){
        *it = toupper(*it);
    }
    //输出
    cout << s2 << endl;
    return 0;
}