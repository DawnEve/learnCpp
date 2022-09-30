#include<iostream>
#include<list>
using namespace std;

int main(){
    list<int> ilist;
    //将元素添加到ilist开头
    for(size_t ix=0; ix!=4; ++ix){
        ilist.push_front(ix);
    }

    // 打印
    for(auto i : ilist)
        cout << i << ", ";
    cout << endl;

    return 0;
}