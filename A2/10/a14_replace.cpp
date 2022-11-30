#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;

void print2(list<int> ctn){
    for(auto ele: ctn)
        cout << ele << " ";
    cout << endl;
}

void demo1(){
    list<int> ilist={1,2,3,4,2};
    //1. 把2替换为 200
    replace(ilist.begin(), ilist.end(), 2, 200);
    print2(ilist);
}

void demo2(){
    list<int> ilist={1,2,3,4,2};
    // 2. replace 的 copy 版本: 第三个参数是迭代器，指出替换后序列的保存位置
    vector<int> ivec;
    replace_copy(ilist.cbegin(), ilist.cend(), 
        back_inserter(ivec), 2, 200);
    print2(ilist); //原容器不变

    // ivec 是ilist 的拷贝，并做了修改
    for(auto ele: ivec)
        cout << ele << " ";
    cout << endl;

}

int main(){
    demo1();
    demo2();

    return 0;
}