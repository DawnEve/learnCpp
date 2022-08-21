#include<iostream>
using namespace std;

//检查IO状态的条件: cin.fail()
int main(){
    int i;
    cout << "input an int:" << endl;
    cin >> i;

    if(!cin.fail())
        cout << "yes, i=" << i << endl;
    else
        cout << "no, i=" << i << endl;

    return 0;
}