#include<iostream>
using namespace std;

//数组作为参数
void print(const int *p){
    cout << p << ", *p="<< *p<< endl;
};
void print2(const int arr[]){  //函数的意图是作用于一个数组
    cout << arr << ", arr[0]="<< arr[0] << endl;
}
void print3(const int arr[10]){  //这里的维度是我们期望的维度，实际不一定
    cout << arr << ", arr[0]="<< arr[0] << endl;
}

int main(){
    int arr2[]={10,20,30};
    int *ptr=arr2;

    print(ptr);
    print2(arr2);
    print3(ptr);

    return 0;
}