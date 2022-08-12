#include<iostream>
#include<cassert>
using namespace std;

//assert 常用语检查不能发生的条件
double divide(int x, int y){
    assert(y!=0);
    cout << ">> this line after asssert;" << endl;
    return static_cast<double>(x) /y;
}

int main(){
    cout << divide(10,3) << endl;
    cout << divide(10,0) << endl;

    return 0;
}