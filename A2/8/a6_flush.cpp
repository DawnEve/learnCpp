#include<iostream>
using namespace std;

//刷新输出缓冲区
int main(){
    int flag=0;
    cout << "1 hi!" << endl; //输出hi和一个换行，然后刷新缓冲区
    cout << "2 hi!" << flush; //输出hi，然后刷新缓冲区，不附加任何额外的字符
    if(flag)
        cout << "|" << endl;

    cout << "3 hi!" << ends; //输出hi和一个空字符，然后刷新缓冲区
    if(flag)
        cout << "|" << endl;
}