#include<iostream>

using namespace std;

//命名： 用户自定义名字不能出现两个下划线，也不能以下划线加大写字母开头。函数内定义的标识符不能下划线开头。

int __ident1=1;
int _Ident2=2;

int main(){
    int _ident3=3;

    cout << "__ident1:" << __ident1 << endl;
    cout << "_Ident2:" << _Ident2 << endl;
    cout << "_ident3 in main:" << _ident3 << endl;
    return 0;
}