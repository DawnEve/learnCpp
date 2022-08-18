#include<iostream>
using namespace std;

//默认初始化
int main(){
    {
        int i=1000, j, x[2];
        cout << j << endl;
        cout << x[0] << "\t" << x[1] << endl;
    }
    //cout << i << endl; //error: ‘i was not declared in this scope

    return 0;    
}