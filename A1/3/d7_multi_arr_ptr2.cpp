#include<iostream>
using namespace std;

// 指向数组的指针，定义时不能省略圆括号
int main(){
    // 不能省略圆括号！否则就从指向数组的指针，变为 指针构成的数组。
    int *ip1[4]; // 整型指针的数组: 先看 ip[4] 是个4元素数组，再看左侧，每个元素是 int*
    int (*ip2)[4]; // 指向含有4个整数的数组的指针

    // 1. int *ip[4] 等价于  int *(ip[4])，默认从右向左看
    int a=1, b=2, c=3, d=4;
    ip1[0]=&a;
    cout << *ip1[0] << "\t" << *(ip1[0]) << endl;

    // 2.  int (*ip)[4]; 从内向外解读：*ip 首先ip是一个指针，看右侧 指向的是一个4元素数组，看左侧，每个元素是int
    int arr[]={0,1,2,3};
    ip2= &arr; //这个赋值的 & 也不能省略！

    for(int i=0; i<4; i++){
        cout << (*ip2)[i] << "\t"; //注意，圆括号必须！
    }
    cout << endl;

    return 0;
}