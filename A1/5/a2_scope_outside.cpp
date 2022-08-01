#include<iostream>
#include<vector>
using namespace std;

// 其他地方需要的，需要定义在局部之外
int main(){
    vector<int> arr={1,2,3,-5,7};

    //寻找第一个负数
    auto beg=arr.begin();
    while(beg != arr.end() && *beg>=0){
        ++beg;
    }
    if(beg == arr.end()){
        cout << "not found" << endl;
    }else{
        cout << *beg << endl;
    }

    return 0;
}