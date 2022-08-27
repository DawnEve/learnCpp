#include<iostream>
#include<fstream>
using namespace std;

// 每次调用 open 时都会确定打开模式
int main(){
    ofstream out; // 未指定文件打开模式
    out.open("a14.txt"); //模式隐含设置为输出和截断
    out.close(); //关闭out(原文件已经清空了)。以便我们用于其他文件。

    out.open("a13.txt", ofstream::app); //模式为输出和追加
    out << "hi, Tom" << endl;
    out.close();

    return 0;
}