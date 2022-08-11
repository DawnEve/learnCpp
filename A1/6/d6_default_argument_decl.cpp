#include<iostream>
using namespace std;

//默认实参只能声明一次
int add(int, int, int z=10); //最后一个有默认实参
// 形参的名字无关紧要
int add(int, int y2=20, int ); //再次声明时，为没有默认值的提供默认值
// 甚至不要形参名字，默认值只给类型
int add(int = -12, int y3, int );

int main(){
    cout << add() << endl; //不要参数，全部使用默认值
    cout << add(1) << endl;
    cout << add(1, 100) << endl;
    cout << add(1, 100, 300) << endl;
    //cout << add(1, z=100) << endl; //error: ‘z was not declared in this scope

    return 0;
}

//函数实现时，可以不管其他值
int add(int x, int y, int z){
    return x+y+z;
}