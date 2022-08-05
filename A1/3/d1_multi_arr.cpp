#include<iostream>
using namespace std;

//多维数组
int main(){
    //定义
    int marr[3][4]; //大小为3的数组，每个元素是含有4个整数的数组

    //大小为10的数组，每个元素都是大小为20的数组，这些数组的元素是含有30个整数的数组
    int marr2[10][20][30]={0}; //将所有元素初始化为0

    cout << sizeof(marr)/sizeof(int) << endl;
    cout << sizeof(marr2)/sizeof(int) << endl;

    return 0;
}