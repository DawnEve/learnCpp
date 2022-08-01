#include<iostream>
using namespace std;

//程序员保证数组下标不越界，否则运行时错误
int main(){
    int arr[3]={10,2,3};
    for(auto i : arr)
        cout << i << " ";
    cout << endl;
    // 越界的也不报错 ??
    cout << "arr[5]   =" << arr[5] << endl; //越界，访问 合法区域，不报错，只是值不确定。
    cout << "arr[5000]=" <<arr[5000] << endl; //越界，并访问非法内存区域时，才报错
    //Segmentation fault (core dumped)
    return 0;
}