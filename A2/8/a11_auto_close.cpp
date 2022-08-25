#include<iostream>
#include<fstream>
using namespace std;

// main 函数接受一个要处理的文件列表(P196, 6.2.5)
int main(int argc, char *argv[]){
    //对每个传递来的文件执行循环
    int i=0;
    for(auto p=argv +1; p!=argv + argc; ++p){
        i++; //文件编号
        ifstream input(*p); //创建输出流并打开文件
        if(input) {   //如果文件打开成功，“处理”该文件
            // process file
            string str;
            while(getline(input, str)){
                cout << i << ": " << str << endl;
            }
        }else{
            cerr << "Open file failed: " + string(*p);
        }
    } //每个循环步骤 input 都会离开作用域，因此会被销毁
}

/*
$ g++ a11_auto_close.cpp 
$ ./a.out a8_file.txt a8_file2.txt
1: S1 4 20.1
1: S2 1 30.5
2: S1 40
2: S2 10
*/