#include<iostream>
#include<array>
using namespace std;

// 列表初始化，使用
int main(){
    array<int, 10> arr={1,2,3};

    for(auto i: arr){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}