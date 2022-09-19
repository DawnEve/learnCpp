#include<iostream>
#include<vector>
#include<list>
#include<forward_list>
#include<deque>
using namespace std;

// 顺序容器的构造函数：容器大小，可选初始值
int main(){
    vector<int> ivec(10, -1);      //10个int元素，每个都初始化为-1
    list<string> svec(10, "hi!");   //10个strings; 每个都初始化为 "hi!"
    forward_list<int> ivec2(10);    //10个元素，每个都初始化为0
    deque<string> svec2(10);   //10个元素，每个都是空string
    
    return 0;
}