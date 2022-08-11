#include<iostream>
using namespace std;

//强制类型转换：大的算术类型赋值给小的类型时
int main(){
    int j=10, i=3;
    double dj=12345678910.5;

    short slope0 = dj / i; //无警告
    long double slope1 = (double)j / i; //C风格的
    double slope = static_cast<double>(j) / i;

    cout << slope0 << endl;
    cout << slope1 << endl;
    cout << slope << endl;

    j= dj - 12345678908.66; //没看到啥warning
    cout << j << endl;

    return 0;
}