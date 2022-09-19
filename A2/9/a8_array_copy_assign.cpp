#include<iostream>
#include<array>
using namespace std;

// 对内置数组不能拷贝或赋值，但是array可以
int main(){
    int arr[]={1,2,3};
    //int arr2[3]=arr;//error: array must be initialized with a brace-enclosed initializer
    int arr3[3];
    //arr3=arr;  // 错误: 内置数组不支持拷贝或赋值
    //error: invalid array assignment

    // part2
    array<int, 3> arrB={1,2,3};
    array<int, 3> arrB2=arrB; //正确：只要数组类型匹配即合法

    for(auto i: arrB2)
        cout << i << " ";
    cout << endl;

    return 0;
}