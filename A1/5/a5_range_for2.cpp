#include<iostream>
#include<vector>
using namespace std;

// range -for, 与之等价的 传统 for 
int main(){
    vector<int> vec={0,1,2,3,4,5};
    // 写时，必须是引用
    for(auto &i : vec){
        i=i*2;
    }
    //等价的传统 for 循环
    for(auto beg=vec.begin(), end=vec.end(); 
        beg!=end; 
        ++beg){
        auto &ref=*beg; //ref 是 beg迭代器指向的值的引用，这样才能执行写操作
        ref *= 2;
    }

    for(auto i : vec)
       cout << i << " ";
    cout << endl;
    return 0;
}