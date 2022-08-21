#include<iostream>
using namespace std;

// getline 函数： 怎么读取一句，而不是一个单词？
// 看来是标准库函数 std::getline
string &myGetline(istream &is, string &line){
    cin >> line;
    return line;
}

int main(){
    string a1;
    cout << "a1=" << a1 << endl;
    //1
    cout << "\t1 Input a line, only get one word:" << endl;
    a1=myGetline(cin, a1);
    cout << "a1=" << a1 << endl;
    // pass当前行多余的单词
    while(getchar() !='\n' ){
        continue;
    } //空语句

    //2
    string a2;
    cout << "\t2 Input a line, get one line:" << endl;
    getline(cin, a2);
    cout << "a2=" << a2 << endl;

    return 0;
}