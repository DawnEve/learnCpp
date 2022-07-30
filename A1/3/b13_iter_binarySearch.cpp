#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> ivec={-20,0,8,10,20,50};
    auto begin=ivec.begin(), end=ivec.end();
    auto mid=begin + ivec.size()/2; //中间点

    int value = 15;
    cout << "Please input a value you want to find: [" << 
            ivec[0] << ", " << ivec[ivec.size()-1] << "]" << endl;
    cin >> value;

    // 当还没有到达终点，且还没有找到目标值时，循环
    while (mid != end && *mid!=value){
        cout << ">> value of begin, mid, end:" << *begin << ", " << *mid << ", " << *end << endl;
        if(value < *mid){
            end=mid; //为什么不需要+1
        }else{
            begin=mid+1; //为什么需要加1？
        }
        mid = begin + (end-begin)/2; //新的中点
    }
    //如果 mid==end 说明没有找到我们需要的值
    if(mid == end){
        cout << "not found" << endl;
    }else{
        cout << *mid << endl;
    }

    return 0;
}