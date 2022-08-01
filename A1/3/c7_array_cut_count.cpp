#include<iostream>
using namespace std;

// 使用数组做分段统计: 0-100 每10分一个段，共11个段，最后一个段只有100一个分数
int main(){
    unsigned scores[11]={}; //存放11个段位统计数
    unsigned grade;
    cout << "Please input some numbers [0,100]: " << endl;
    while (cin >> grade){
        if(grade<=100){
            ++ scores[grade/10];
        }
    }
    // output
    for(auto i : scores){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}