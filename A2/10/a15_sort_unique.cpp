#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void print(vector<string> svec, int i=0){
    cout << i << " ";
    for(auto ele: svec)
        cout << ele<< " ";
    cout << endl;
}

int main(){
    vector<string> svec={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    print(svec);
    //1.排序: 按字典顺序升序 a-z
    sort(svec.begin(), svec.end());
    print(svec,1);
    //2.unique 重排，每个单词只出现一次；返回值是迭代器，指向unique区域之后的一个位置
    auto uniq_next = unique(svec.begin(), svec.end());
    print(svec,2);
    cout << *(uniq_next-1) << endl;
    
    //3.删除其余的元素
    svec.erase(uniq_next, svec.end());
    print(svec,3);
    return 0;
}