#include<iostream>
using namespace std;

//值初始化 2
void counter(){
    static int cnt;
    cout << cnt++ << endl;
}

int main(){
    for(int i=0; i<5; i++)
        counter();
    return 0;
}