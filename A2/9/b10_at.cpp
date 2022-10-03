#include<iostream>
#include<vector>
using namespace std;

// 下标越界，at 会报异常
int main(){
    vector<string> svec={"this", "is"};
    cout << svec[0] << endl;
    //cout << svec[2] << endl; //运行时错误: svec 中没有这个元素
    // Segmentation fault (core dumped)

    cout << svec.at(1) << endl;
    //cout << svec.at(2) << endl; //抛出一个 out_of_range 异常
    //terminate called after throwing an instance of 'std::out_of_range'
}