#include<iostream>
using namespace std;

//函数返回类型知道是某个数组，就可以使用 decltype 来定义返回类型
int odd[]={1,3,5};
int even[]={2,4,6};

//返回一个指针，指向含有3个整数的数组
decltype(odd) *choose(int i){ 
    //注意：decltype 并不负责把数组类型转换成对应的指针，所以 decltype 的结果是个数组
    // 想要返回指向数组的指针，还要在函数声明前加上*符号
    return i %2 ? &odd : &even;
}

int main(){
    decltype(odd) *arr1=choose(0);
    decltype(odd) *arr2=choose(1);

    cout << odd << endl;
    cout << even << endl;

    cout << arr1 << endl;
    cout << arr2 << endl;

    return 0;
}