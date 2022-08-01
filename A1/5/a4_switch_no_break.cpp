#include<iostream>
using namespace std;

//没有break，则case每个分支都会执行到
int main(){
    unsigned vowelCnt=0, others=0;
    char ch;
    // 忽略掉了空白字符
    while(cin >> ch){
        switch(ch){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                ++vowelCnt;
                break;
            default:
                cout << ch;
                ++others;
        }
    }
    cout << endl;

    cout << "the number of vowel:" << vowelCnt << endl;
    cout << "the number of other chars:" << others << endl;
    return 0;
}