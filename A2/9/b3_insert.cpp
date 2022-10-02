#include<iostream>
#include<list>
using namespace std;

// 插入一个元素：在迭代器指向位置之前插入，迭代器所在元素的地址不变
int main(){
    list<int> arr={1,3,5,7};
    auto iter=arr.end();
    iter--;
    cout << *iter << ", addr:" << &*iter << endl;

    arr.insert(iter, 900);
    //打印
    for(auto i: arr)
        cout << i << ", ";
    cout << endl;
    cout << *iter << ", addr:" << &*iter << endl;

    return 0;
}