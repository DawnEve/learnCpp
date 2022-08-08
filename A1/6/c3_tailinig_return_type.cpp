#include<iostream>
using namespace std;

int arr[]={10,1,2,3,4};

//C++ 尾置返回类型
auto init(int i)-> int (*)[5]{
    arr[i]=0;
    return &arr;
}

int main(){
    int arr2[]={10,20,30,40,50};
    int (*p)[5] = init(4);

    for(auto i : arr){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}