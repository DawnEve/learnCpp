#include<iostream>
using namespace std;

// 指针 与 多维数组
int main(){
    int ia[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12}; //大小为3，每个元素是4整数一维数组
    int (*p)[4] = ia; //p指向含有4个整数的数组

    // 输出
    for(int i=0; i<4; i++)
        cout << (*p)[i] << endl;
    cout << endl;

    // 重新赋值
    p=&ia[2]; //p指向ia的尾元素
    for(int i=0; i<4; i++)
        cout << (*p)[i] << endl;

    return 0;
}