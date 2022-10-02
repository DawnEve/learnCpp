#include<iostream>
#include<vector>
#include<list>
using namespace std;

int main(){
    list<string> slist;
    vector<string> svect;

    //等价于 
    slist.push_front("list.");
    slist.insert(slist.begin(), "Hello!");

    // vector 不支持 push_front，但是也可以插入 begin() 之前
    // 警告：插入到 vector 末尾之外的位置都可能很慢
    svect.insert(svect.begin(), "vect");
    cout << "addr:" << &*(svect.begin()) << endl;

    auto be=svect.begin();
    cout << *be << " | addr:" << &*(be) << endl;
    svect.insert(be, "Hello!");
    //cout << *be << " | addr:" << &*(be) << endl;//Segmentation fault (core dumped)


    // 打印
    for(auto i : slist)
        cout << i << " ";
    cout << endl;

    for(auto i : svect)
        cout << i << " ";
    cout << endl;

    return 0;
}