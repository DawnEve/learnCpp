#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<unsigned> scores(11, 0); //11个段位，全部初始化为0
    unsigned grade; //得分
    cout << "Please input some scores from 0 to 100:" << endl;
    while(cin >> grade)
        if(grade <= 100)
            ++scores[grade/10];
    // output result
    for(int i=0; i<scores.size(); i++)
        cout << scores[i] << "  ";
    cout << endl;
    return 0;
}