#include<iostream>
using namespace std;

//使用流之前，检查它是否处于良好状态：把它作为一个条件
int main(){
    int i;
    cout << "input an int:" << endl;
    if( cin >> i){
        cout << "yes, i=" << i << endl;
    }else{
        cout << "no, i=" << i << endl;
    }
    return 0;
}