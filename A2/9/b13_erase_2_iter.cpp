#include<iostream>
#include<list>
using namespace std;

// 删除2个迭代器范围内的
// 返回被删元素下一个位置
int main(){
    list<string> slist={"this", "is", "a", "very", "good", "book"};
    for(auto i : slist)
        cout << i << " ";
    cout << endl;

    // 删除迭代器范围内的元素
    auto it1=slist.begin(), it2=slist.end();
    it1++;
    it1++;
    it2--;
    cout << "*it1=" << *it1 << endl;
    cout << "*it2=" << *it2 << endl;

    //删除
    auto it3=slist.erase(it1, it2);

    cout << "\n==> After erase:" << endl;
    cout << "*it1=" << *it1 << endl;
    cout << "*it2=" << *it2 << endl;
    cout << "*it3=" << *it3 << endl;

    for(auto i : slist)
        cout << i << " ";
    cout << endl;

}