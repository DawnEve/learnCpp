#include<iostream>
#include<vector>
using namespace std;

int main(){
    //方法1: 最好
    vector<int> ivec1(10, 42);

    //方法2
    vector<int> ivec2{42,42,42,42,42,42,42,42,42,42};

    //方法3
    vector<int> ivec3(10);
    for(int &i : ivec3)
        i=42;
    
    //输出检查
    for(int i: ivec1)
        cout << i << " ";
    cout << endl;
    
    return 0;
}