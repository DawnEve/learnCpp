#include<iostream>
#include<iterator>
#include<vector>
using namespace std;

int main(){
    vector<int> vec={1,2,3};
    auto it=back_inserter(vec); //返回迭代器
    *it=42; //调用 push_back，把等号右侧的元素添加到原容器中
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl;

    return 0;
}