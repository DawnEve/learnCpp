#include<iostream>
using namespace std;

// 构造函数：初始值列表
class Time{
    string name="";
    int time[3];
public:
    //参数列表后、函数体前：冒号以及冒号后的，类成员用逗号分割，括号(或花括号)内是形参。
    Time(int h, int m, int s): time{h, m, s}{} 
    Time(int h, int m, int s, const string &clockName): time{h, m, s}, name(clockName){}
    void now(){
        cout << "clockName:" << name << ",\ttime: ";
        for(auto i : time)
            cout << i << ":";
        cout << endl;
    }
};

int main(){
    Time t1(5,10,3);
    t1.now();

    Time t2(5,10,3, "getUp");
    t2.now();

    return 0;
}