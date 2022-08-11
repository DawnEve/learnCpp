#include<iostream>
using namespace std;

// 获取字符的地址
//https://blog.csdn.net/Master_0_/article/details/123793762
int main(){
    char s1='c', s2='x';
    cout << &s1 << endl; //获取地址，为什么总是失败？ 因为cout总是想把字符读取到\0结尾为止

    //check
    char arr[]={'h', 'i', ',', '\0'};
    cout << &(arr[0]) << endl; //想要第一个字符的地址，但是一直输出字符，直到 \0 才停止
    cout << (void *)&(arr[0]) << endl; //第一个字符的地址

    //solution
    printf("method1: &s1=%p\n", &s1); //方法1: 使用C的printf
    cout << "method2: &s1=" << (void *)&s1 << endl; //方法2: 强制转为空指针

    return 0;
}