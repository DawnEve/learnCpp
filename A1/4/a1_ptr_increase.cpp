#include<iostream>
using namespace std;

// *p++ 等价于 *(p++)
int main(){
    int arr[]={10,1,2,3,4,5};
    int *p=arr;

    while(p != end(arr)){
        cout << *p++ << endl;
    }
    return 0;
}