#include<iostream>
#include<list>
using namespace std;

// 赋值
int main(){
    list<int> c1={1,2,3};

    // 1.拷贝
    list<int> c2=c1;

    for(auto i: c2)
        cout << i << ", ";
    cout << endl;

    // 2.赋值
    c2={1,2,3,4,5};

    for(auto i: c2)
        cout << i << ", ";
    cout << endl;

    return 0;
}