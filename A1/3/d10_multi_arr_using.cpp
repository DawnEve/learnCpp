#include<iostream>
using namespace std;

//使用类型别名，简化多维数组的指针
int main(){
    // 如下2行声明等价
    //using int_arr4 = int[4]; //新标准下类型别名的声明，见 2.5.1
    typedef int int_arr4[4]; //等价的 typedef 声明

    int arr[2][4]={1,2,3,4, 10,20,30,40};
    
    //output
    for(int_arr4 *p=arr; p!=arr+2; ++p){
        for(int *q=*p; q!=*p+4; ++q){
            cout << *q << "\t";
        }
        cout << endl;
    }
    return 0;
}