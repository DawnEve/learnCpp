#include<iostream>
#include<list>
#include<vector>
using namespace std;

// 列表初始化
int main(){
    // 每个元素三个元素，用给定的初始化器进行初始化
    list<string> authors = {"Milton", "Shakespeare", "Austen"};
    vector<const char*> articles={"a", "an", "the"};

    for(auto i: authors)
        cout << i << " ";
    cout << endl;

    for(auto i: articles)
        cout << i << " ";
    cout << endl;

    return 0;
}