#include<iostream>
using namespace std;

// 数组自带结束标记：C风格字符串
void print(const char *cp){
    if(cp) // 非空指针
        while(*cp) //不能是结尾 '\0'
            cout << *cp++; //输出当前字符，并指针向后移动一位
}

int main(){
    char s2[]="this is a book.";
    print(s2);

    cout << endl;
    return 0;
}