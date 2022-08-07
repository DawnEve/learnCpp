#include<iostream>
using namespace std;

// 如果for循环中有return，则for后也要有return语句，不是所有编译器都能是识别这一点。
int getIndex(int arr[], int value){
    for(int i=0; i<4; i++){
        if(arr[i] == value){
            return i;
        }
    }

    //return -1;
}

int main(){
    int arr2[]={10,20,30,40};
    cout << getIndex( arr2, 30) << endl;
    cout << getIndex( arr2, 35) << endl; //如果 getIndex 没有最后的 return -1; 则找不到时返回异常值: 40
    return 0;
}