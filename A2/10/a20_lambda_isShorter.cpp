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

void print(vector<string> &svec){
    for(auto ele: svec)
        cout << ele << " ";
    cout << endl;
}

// lambda 表达式：函数的调用
void demo1(){
    auto f=[](const string &s1, const string &s2){
            return s1.size() < s2.size();
       };
    string a1="book", a2="boo";
    cout << f(a1, a2) << endl;
    a2="books";
    cout << f(a1, a2) << endl;
}

// 使用 lambda 表达式排序
void demo2(){
    vector<string> svec2={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    //1.字典排序，去重
    elimDups(svec2); 
    print(svec2);
    //2.按长度排序，等长的按字典序; 
    // 参数3: lambda 表达式 代替函数 isShorter
    stable_sort(svec2.begin(), svec2.end(),  
       [](const string &s1, const string &s2){
            return s1.size() < s2.size();
       } );
    print(svec2);
}

int main(){
    demo1();
    demo2();
    return 0;
}