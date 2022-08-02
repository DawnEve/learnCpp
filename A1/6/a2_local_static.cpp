#include<iostream>
using namespace std;

// 函数被调用次数，局部静态对象
int counter(){
    static int count=0; //函数调用结束，这个值仍然有效
    return ++count;
}

int main(){
    for(int i=0; i<5; i++){
        cout << "call counter: " << counter() << endl;
    }
    return 0;
}