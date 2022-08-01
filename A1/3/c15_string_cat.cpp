#include<iostream>
#include<cstring>
using namespace std;

// 字符串的连接
int main(){
    // 2个 string 对象的连接
    string s1="hello";
    string s2="world";
    string s3=s1+" "+ s2;
    cout << s3 << endl;

    // 2个 C 风格的字符串的连接
    char c1[]="hello";
    char c2[]="world";

    //要先声明一个大数组, 貌似估算错了也没有影响
    //char c3[500];
    char c3[5];
    strcpy(c3, c1);
    strcat(c3, " ");
    strcat(c3, c2);
    //cout << c3 << endl;
    char *p=c3;
    while(*p != '\0'){
        putchar(*p);
        p++;
    }
    putchar('\n');

    return 0;
}