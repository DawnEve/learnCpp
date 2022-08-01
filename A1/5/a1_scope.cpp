#include<iostream>
using namespace std;

int get_num(){
    int x;
    cin >> x;
    return x;
}

// 变量在控制结构内的定义，只在内部可见
int main(){
    cout << "Please input some numbers, exit when <0:" << endl;
    //1. while
    while(int i = get_num() ){
        cout << i << endl;
        if (i<0)
            break;
    }
    //i=1; //error: ‘i was not declared in this scope
    return 0;
}