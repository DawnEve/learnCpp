#include<iostream>
using namespace std;

//数组作为auto变量的初始值，推断其为指针，而不是数组
int main(){
    int  arr[3]={10, 11, 12};
    auto arr2(arr); //arr 是一个数组，作为auto 类型arr2的初始值时
    //arr2=4; //error: invalid conversion from ‘int’ to ‘int*’ [-fpermis]ive
    
    //arr=4; //error: incompatible types in assignment of ‘int’ to ‘int [3]’

    cout << arr2 << endl;
    cout << *arr2 << endl;
    cout << *(arr2+1) << endl; //可以递增，获取下一个元素，因为数组在内存区是连续的

    return 0;
}