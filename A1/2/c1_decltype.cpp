#include<iostream>
using namespace std;

//decltype 获得的是不是引用，怎么区分？
// 能获得值，能修改值，则是引用，是引用就要初始化。

int main(){
    int i=42, *p=&i, &r=i;
    decltype(r+0) b; //正确：加法的结果是int，因此b是一个(未初始化的) int
    
    //decltype(*p) c;  //错误: c是 int&, 必须初始化
    // error: ‘c declared as reference but not initialized

    b=20;
    cout << b << endl;

    return 0;
}