#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

int main(){
    vector<int> ivec={1,3,5,7};
    // 对vec中的元素求和，和的初始值是0
    int sum=accumulate(ivec.begin(), ivec.end(), 0);
    cout << "sum="  << sum << endl;
    return 0;
}