#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> vec;
    cout << vec.size() << endl;

    vec={1,2,3};
    cout << vec.size() << endl;
    fill_n(vec.begin()+1, 2, 100); //从下标1开始的2个位置，填充值100
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl;

    return 0;
}