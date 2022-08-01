#include<iostream>
#include<vector>
using namespace std;

// range -for
int main(){
    vector<int> vec={0,1,2,3,4,5};
    // 写时，必须是引用
    for(auto &i : vec){
        i=i*2;
    }
    //读时，不做要求
    for(auto i : vec){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}