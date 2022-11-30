#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void elimDups(vector<string> &svec){
    //排序
    sort(svec.begin(), svec.end());
    //保持唯一
    auto iter=unique(svec.begin(), svec.end());
    //删除后面的重复元素
    svec.erase(iter, svec.end());
}

// 按单词的长度排序
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

int main(){
    vector<string> svec2={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    //1.按字典排序，去重
    elimDups(svec2);
    for(auto ele: svec2)
        cout << ele << " ";
    cout << endl;

    //2. 按长度排序，长度相同的保持字典序
    stable_sort(svec2.begin(), svec2.end(), isShorter);
    for(const auto &s: svec2) //无需拷贝字符串
        cout << s << " ";
    cout << endl;

    return 0;
}