#include<iostream>
#include<vector>
using namespace std;

//值初始化 3
int main(){
    vector<int> arr(5); //5个值，每个都是0
    //vector<int> arr2(5, 20); //5个值，每个都是20
    for(auto i : arr)
        cout << i << endl;
    return 0;
}