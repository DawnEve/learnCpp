#include<iostream>
using namespace std;

// 返回空
void swap(int &i1, int &i2){
    // 如果相等，直接返回
    if(i1==i2)
        return;
    // 如果不等，则交换值
    int tmp=i1;
    i1=i2;
    i2=tmp;
    //此处无须显示return语句。
}

int main(){
    int x=10, y=-80;
    cout << "x=" << x << ", y=" << y << endl;
    swap(x, y);
    cout << "x=" << x << ", y=" << y << endl;

    return 0;
}