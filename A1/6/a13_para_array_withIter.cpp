#include<iostream>
using namespace std;

// 传递指向首元素和尾后元素的指针/迭代器
void print(const int *begin, const int *end){
    //输出之间的值
    while(begin<end)
        cout << *begin++ << endl; // 输出当前值，并后移一位
}

int main(){
    int arr[]={10,20,30,40};
    //print(begin(arr), end(arr));
    //print(arr, end(arr)); //效果同上
    print(arr, arr + sizeof(arr)/sizeof(int) ); //效果同上

    return 0;
}