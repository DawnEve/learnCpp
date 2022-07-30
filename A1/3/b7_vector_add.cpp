#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> iVec; //声明空vector
    //iVec[0]=12; //编译通过，运行时 Segmentation fault (core dumped)

    //正确的做法是使用 push_back() 方法添加
    iVec.push_back(12);

    return 0;
}