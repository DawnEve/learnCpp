#include<iostream>
#include<array>
using namespace std;

// array 可以赋值
int main(){
    array<int, 5> arr1={0,1,2,3,4};
    array<int, 5> arr2={100};

    for(auto i: arr2)
        cout << i << " ";
    cout << endl;

    cout << arr2.size() << endl;
    arr2=arr1;
    cout << arr2.size() << endl;

    for(auto i: arr2)
        cout << i << " ";
    cout << endl;

    arr2={-1,-2}; //P302 说这样是错的，我的测试没问题，还符合预期
    for(auto i: arr2)
        cout << i << " ";
    cout << endl;

    return 0;
}