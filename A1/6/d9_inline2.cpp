#include<iostream>
using namespace std;

//证明是否有内联展开 //todo，无解
inline int add(int x, int y){
    return x+y;
}

int main(){
    int result=0;

    cout << "add(1,2)=" << add(1,2) << endl;
    cout << "result=" << result << endl;

    return 0;
}