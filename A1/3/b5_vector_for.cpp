#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> v{1,3,5,7,9};
    for(auto &i : v) //注意 i 是一个引用。
        i *= i; // 对每个i的元素求平方
    
    for(auto i : v) //遍历每个元素，并打印
        cout << i << " ";
    cout << endl;

    return 0;
}