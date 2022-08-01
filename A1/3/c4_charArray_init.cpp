#include<iostream>
using namespace std;

int main(){
    //字符串数组的 字面量初始化，字符串字面量结尾的空字符，也会被拷贝到数组中
    char a1[]={'c', '+', '+'}; //列表初始化，无空字符
    char a2[]={'c', '+', '+', '\0'}; //列表初始化，有空字符

    char a3[]="C++"; //自动添加字符串结尾的空字符，长度为4

    //const char a4[3]="C++"; //错误，没空间存放最后的空字符
    // error: initializer-string for array of chars is too long [-fpermissive]

    cout << "size of a3=" << sizeof(a3)/sizeof(char) << endl;


    return 0;
}