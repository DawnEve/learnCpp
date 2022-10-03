#include<iostream>
#include<vector>
#include<list>
using namespace std;

//弹出元素，返回void
void demo1(){
    vector<int> c={0,1,2};
    c.pop_back();
    //c.pop_front(); //error: ‘class std::vector<int>’ has no member named ‘pop_front’

    for(auto i: c)
        cout << i << " ";
    cout << endl;
}

//弹出元素，返回void
void demo2(){
    list<int> c={0,1,2};
    //c.pop_back();
    c.pop_front();

    for(auto i: c)
        cout << i << " ";
    cout << endl;
}

int main(){
    demo1();
    demo2();
}