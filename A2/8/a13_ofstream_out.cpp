#include<iostream>
#include<fstream>
using namespace std;

// ofsteam 默认使用 out 模式打开文件。指定 app 模式才能保留源文件内容

int main(){
    string s2 = "hello, Tom 01 02 03 04!";
    string fileName="a13.txt";

    // 这几条，file 都被截断
    //ofstream out(fileName); //隐含以输出模式打开文件并截断文件
    //ofstream out(fileName, ofstream::out); //隐含的截断文件
    //fstream out(fileName, ofstream::out  | ofstream::trunc);

    //为了保留原文件内容，必须显式指定 app 模式
    //ofstream out(fileName, ofstream::app); //隐含的输出文件
    ofstream out(fileName, ofstream::out | ofstream::app);

    out << s2 << endl;
    out.close();

    cout << "Please view file: $ cat " << fileName << endl; 

    return 0;
}