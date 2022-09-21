#include<iostream>
#include<vector>
#include<list>

using namespace std;

void print(list<string> l1){
    for(auto i: l1)
        cout << i << " ";
    cout << endl;
}

// assign 的用法
int main(){
    list<string> names;
    vector<const char*> oldStyle = {"Hi!", "How", "are", "you?"};
    //names = oldStyle; //错误：容器类型不匹配
    //error: no match for ‘operator=’

    //正确: 可以将 const char* 转换为 string
    names.assign(oldStyle.cbegin(),  oldStyle.cend());
    print(names);

    // 用法2: 列表
    names.assign( {"this", "is", "a", "book"} );
    print(names);

    // 用法3: (n,t) 填充为n个值为t的元素
    names.assign(3, "is");
    print(names);

    return 0;
}