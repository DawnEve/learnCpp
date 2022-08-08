#include<iostream>
using namespace std;

// 指向数组的指针
int get_by_index(int (*p)[4], int index){
    return (*p)[index];
}

// 简化版
typedef int arrT4[4]; //arrT4是一个类型别名，表示含有4个整数的数组: int [4]
int get_by_index2(arrT4 arr, int index){
    return arr[index];
}

using arrT4_2= int [4]; //arrT4_2 同上
int get_by_index3(arrT4_2 arr, int index){
    return arr[index];
}

int get_by_index4(arrT4_2 *p, int index){
    return (*p)[index];
}

int main(){
    int arr[]={50,10,20,30};
    cout << get_by_index(&arr, 0) << endl;
    cout << get_by_index2(arr, 0) << endl;
    cout << get_by_index3(arr, 0) << endl;
    cout << get_by_index4(&arr, 0) << endl;

    return 0;
}
