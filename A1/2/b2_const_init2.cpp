#include<iostream>
using namespace std;

int main(){
    int i=2;
    int &r1=i;   //r1绑定对象i
    const int &r2=i;  //r2页绑定对象i，但是不允许修改r2的值

    cout << "1 i=" << i << ", r1=" << r1 << ", r2=" << r2 << endl;

    i=10; //修改后，r1和r2都变了
    cout << "2 i=" << i << ", r1=" << r1 << ", r2=" << r2 << endl;

    r1=0; //r1不是常量，i的值为0
    //r2=0; //报错，r2不能修改。
    // error: assignment of read-only reference ‘r2’
    cout << "3 i=" << i << ", r1=" << r1 << ", r2=" << r2 << endl;

    return 0;
}