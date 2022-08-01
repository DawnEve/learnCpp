#include<iostream>
using namespace std;

//指向数组元素的指针，加减整数，表示指针前后移动
int main(){
    int arr[10]={0,1,2,3,4,5,6,7,8,9};
    int *p1=arr; //指向第1个元素 arr[0]
    int *p2=p1+4; //指向第5个元素 arr[4]

    cout << *p1 << " " << arr[0] << endl;
    cout << *p2 << " " << arr[4] << endl;

    cout << p2-p1 << endl;
    return 0;
}