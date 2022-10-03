#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> v={0,1,2,3};
    auto begin=v.begin(), 
        end=v.end(); //保存尾后迭代器是一个坏主意

    // while(begin != end){ //Segmentation fault (core dumped)
    while(begin != v.end()){
        //做一些处理
        *begin = - *begin; // 改变符号
        // 插入新值，对begin 重新赋值，否则的话它就会失效
        ++begin;  //向前移动begin()，因为我们想在此元素后插入元素
        begin = v.insert(begin, 100); //插入新值
        ++begin; //向前移动，跳过新插入的值
    }

    // 打印结果
    for(auto i: v)
        cout << i << " ";
    cout << endl;

}