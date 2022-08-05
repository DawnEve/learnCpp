#include<iostream>
using namespace std;

//数组引用形参 fn(int (&arr)[3]) 注意，(%arr) 的圆括号不能省略
//void change(int &arr[3]){ //error: declaration of ‘arr’ as array of references
void change(int (&arr)[3]){
    cout << sizeof(arr)/sizeof(int) << endl; //能获取长度
    arr[0]=1024; //能修改数组的值
}


int main(){
    int i1=1, i2=2, i3=3, arr2[]={10,20,30};
    change(arr2);
    cout << arr2[0] << endl;

    return 0;
}