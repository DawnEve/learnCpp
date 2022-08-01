#include<iostream>
#include<cstring>
using namespace std;

//C 风格的字符串操作
int main(){
    char str1[]={'C', '+', '+'}; //不以空字符结尾
    char str2[]={'C', '+', '+', '\0'}; //以空字符结尾

    cout << strlen(str1) << endl; //返回的长度不对，也可能是一直读取到\0结束
    cout << strlen(str2) << endl; 

    return 0;
}