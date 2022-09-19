#include<iostream>
#include<list>
#include<deque>
using namespace std;

int main(){
    list<string> authors = {"Milton", "Shakespears", "Austen"};

    // it是指向 authors 某个元素的迭代器
    auto it=authors.end();
    it--;

    // 用一对迭代器拷贝元素: 从参数1 复制到 参数2(不含)所指向的元素
    deque<string> authList(authors.begin(), it);

    // 输出
    for(auto i:authList){
        cout << i << ", ";
    }
    cout << endl;

    return 0;
}