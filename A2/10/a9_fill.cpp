#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> ivec={0,1,2,3,4,5};
    //每个元素重置为0
    fill(ivec.begin(), ivec.end(), 0);
    //输出
    for(auto ele: ivec){
        cout << ele << endl;
    }
    printf("\n");

    //子序列重置为5
    fill(ivec.begin(), ivec.begin()+ivec.size()/2, 5);
    //输出
    for(auto ele: ivec){
        cout << ele << endl;
    }

    return 0;
}