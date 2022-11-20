#include<iostream>
#include<algorithm>
using namespace std;

//内置数组上使用 find 查找值
int main(){
    int arr[]={1,2,3,4,5}, len=sizeof(arr)/sizeof(int);
    printf("begin(arr):%p, arr:%p\n", begin(arr), arr); //首元素地址
    printf("end(arr):%p, arr+len:%p\n", end(arr), arr+len); //尾后位置地址
    // 一个给定的值
    int val=30;
    int* result=find(begin(arr), end(arr), val);
    printf("result:%p, arr+len:%p\n", result, arr+len);
    cout << "The value " << val << 
        (result==arr+ len ? " is NOT in arr": " is in arr") << endl;
    return 0;
}