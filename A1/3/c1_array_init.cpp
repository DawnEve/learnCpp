#include<iostream>
using namespace std;

int arr0[10]; //含有10个元素的数组
//函数内的内置类型的数组，初始化时含有未定义的值。比如 arr

int main(){
    //数组的初始化
    int arr[10]; //含有10个元素的数组

    unsigned cnt=20; //不是常量表达式
    constexpr unsigned sz=25; // 常量表达式
    int *parr[sz]; //含有25个整型指针的数组

    string bad[cnt]; //报错：cnt不是常量表达式。为啥我测试没报错呢？
    cout << "|" << bad[0] << "| length=" << bad->length()  << endl;
    cout << "|" << arr0[0] << "| outsize function, do default init " << endl;
    cout << "|" << arr[0] << "| inside function, not do default init" << endl;

    //string strs[get_size()]; //当 get_size 是 constexpr 时正确，否则错误。

    return 0;
}