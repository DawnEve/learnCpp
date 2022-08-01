#include<iostream>
using namespace std;

//指向数组元素的指针，可以使用下标运算符。
int main(){
    int arr[]={0,1,2,3,4,5};
    int *p1=arr;
    int *p2=p1+2;

    cout << "arr[1]=" << arr[1] << endl;
    cout << "p1[1]=" << p1[1] << endl;
    cout << "p2[1]=" << p2[1] << endl;
    cout << "p2[0]=" << p2[0] << ", *p2=" << *p2 << endl;
    cout << "p2[-1]=" << p2[-1] << endl; //下标可以为负

    return 0;
}