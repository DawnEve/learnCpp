#include<iostream>
using namespace std;

int main(){
    int len=5;
    int arr[len];

    len=9;
    for(int i=0; i<len; i++)
       cout << i <<", addr=" << &(arr[i])  << "\t" << arr[i] << endl;
    
    cout << "size of arr:" << sizeof(arr) << endl;
    cout << "element number:" << sizeof(arr)/sizeof(int) << endl;
    return 0;
}