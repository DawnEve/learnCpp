#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    string text="this is a book.";
    // v3: 基于 range-for 的迭代输出
    //遍历，直到遇到空格停止
    for(auto i : text){
        if(i == ' ')
            break;
        cout << i << " ";
    }
    cout << endl;

    return 0;
}