#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// 按单词的长度排序
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

int main(){
    vector<string> svec={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    sort(svec.begin(), svec.end(), isShorter); //参数3是函数
    for(auto ele: svec)
        cout << ele << " ";
    cout << endl;
    return 0;
}