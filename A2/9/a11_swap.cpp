#include<iostream>
#include<list>
using namespace std;

void print(const list<int> &l0){
    cout << ">> &l0: " << &l0 << endl;
    for(auto i: l0)
        cout << i << " ";
    cout << endl;
}


// swap 的使用
int main(){
    list<int> l1={0,1,2};
    list<int> l2={0,10,20};

    //l1.swap(l2);
    swap(l1, l2);
    cout << "&l1: " << &l1 << endl;
    cout << "&l2: " << &l2 << endl;
    print(l1);
    print(l2);

    return 0;
}