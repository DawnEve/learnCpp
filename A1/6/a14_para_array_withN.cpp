#include<iostream>
using namespace std;

// 显式传递一个数组长度参数
void print(int arr[], int N){
    for(int i=0; i<N; i++){
        cout << arr[i] << endl;
    }
}

int main(){
    int arr2[]={10,20,30};
    //print(arr2, sizeof(arr2)/sizeof(int));
    print(arr2, end(arr2) - begin(arr2) ); //效果同上
    return 0;
}