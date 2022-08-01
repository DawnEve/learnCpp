#include<iostream>
using namespace std;

// switch 语句统计元音字母频率
int main(){
    unsigned aCnt=0, eCnt=0, iCnt=0, oCnt=0, uCnt=0, Cnt=0;
    char ch;
    while (cin >> ch){
        // 如果 ch 是元音字母，将其对应的计数器加1
        switch(ch){
            case 'a':
                ++aCnt;
                break;
            case 'e':
                ++eCnt;
                break;
            case 'i':
                ++iCnt;
                break;
            case 'o':
                ++oCnt;
                break;
            case 'u':
                ++uCnt;
                break;
            default:
                ++Cnt;
        }
    }
    //output:
    cout << "Number of vowel a: " << aCnt << '\n'
        << "Number of vowel e: " << eCnt << '\n'
        << "Number of vowel i: " << iCnt << '\n'
        << "Number of vowel o: " << oCnt << '\n'
        << "Number of vowel u: " << uCnt << '\n'
        << "Number of all chars: " << Cnt << '\n'
        << endl;
    return 0;
}