#include<iostream>
#include<array>
using namespace std;

// array 可以赋值
int main(){
    array<int, 5> arr1={0,1,2,3,4};
    array<int, 5> arr2={0};

    // arr1
    cout << arr1.size() << endl;
    arr2=arr1;
    cout << arr1.size() << endl;

    for(auto i: arr1)
        cout << i << " ";
    cout << endl;

    // arr2
    arr2={0};
    for(auto i: arr2)
        cout << i << " ";
    cout << endl;

    return 0;
}