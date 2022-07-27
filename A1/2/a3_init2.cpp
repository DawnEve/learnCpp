#include<iostream>
using namespace std;

int main(){

    long double ld=3.14159265358;
    // 错误: 转换未执行，因为存在丢失信息的风险：小数会丢失，整数可能太大丢失
    //int a1{ld}; //narrowing conversion of ‘ld’ from ‘long double’ to ‘int’
    //int a2={ld};

    // 正确：转换执行，且丢失部分数据。
    int a3(ld);
    int a4=ld;

    //cout << "a1=" << a1 << endl;
    //cout << "a2=" << a2 << endl;
    cout << "a3=" << a3 << endl;
    cout << "a4=" << a4 << endl;

    return 0;
}