#include<iostream>
using namespace std;

//使用迭代器遍历数组
int main(){
    int arr[3]={10, 11, 12};
    // 尾后迭代器，就是最后一个不存在的元素的地址
    int *end=&arr[ sizeof(arr)/sizeof(int) ];
    for(int *be=arr; be != end; ++be){
        cout << *be << endl;
    }
    return 0;
}