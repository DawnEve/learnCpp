#include<iostream>

using namespace std;

int main(){
    int iVal=20;
    int &refVal=iVal; //引用类型，表示 iVal 的另一个名字
    // int &refVal2; //refVal2 declared as reference but not initialized
    int &refVal3=refVal; //refVal 和 iVal 等价，所以 refVal3 也是 iVal 的另一个名字

    cout << "   iVal=" << iVal << "| pointer=" << &iVal << endl;
    cout << " refVal=" << refVal << "| pointer=" << &refVal << endl;
    //cout << "refVal2=" << refVal2 << endl;
    cout << "refVal3=" << refVal3 << "| pointer=" << &refVal3 << endl;

    return 0;
}