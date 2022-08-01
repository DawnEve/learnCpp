#include<iostream>
using namespace std;

//数组初始化，不能拷贝。
// 不能用数组为其他数组赋值。
int main(){
    int a1[]={0,1,2};
    //int a2[]=a1; //error: initializer fails to determine size of ‘a2’
    
    int a2[3];
    a2=a1; //error: invalid array assignment

    return 0;
}