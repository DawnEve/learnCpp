#include<iostream>
using namespace std;

// 显式初始化数组
int main(){
    // 1.指定长度，并使用列表初始化
    const unsigned sz=3;
    int arr1[sz]={0,1,2}; // 含有3个元素的数组，分别是0,1,2
    
    // 2.给出数组元素，编译器根据初始值推断维度
    int arr2[]={0,1,2,3}; //维度是4的数组

    //例外1. 如果维度大，初始值个数少，则其余的默认值
    int arr3[5]={0,1,2}; //等价于 arr3[]={0,1,2,0,0}
    string arr4[3]={"this", "is"}; //等价于 arr4[]={"this", "is", ""}

    //错误: 初始值个数 大于维度则报错
    //int arr5[2]={0,1,2}; // error: too many initializers for ‘int [2]’

    cout << "size of arr2=" << sizeof(arr2)/sizeof(int) << endl;
    for(int i=0; i<sizeof(arr3)/sizeof(int); i++)
        cout << "arr3[" << i << "]=" << arr3[i] << endl;
    
    return 0;
}