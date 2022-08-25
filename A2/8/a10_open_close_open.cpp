#include<iostream>
#include<fstream>
using namespace std;

//读取另一个文件前，要关闭文件。

int main(int argc, char *argv[]){
    string str;
    cout << "input a line: stop with ctrl+D" << endl;
    
    // 从键盘输入
    /*while(getline(cin, str)){
        cout << ">" << str << endl;
    }*/

    // 从2个文件输入
    //ifstream input(argv[1]);
    ifstream input;
    cout << "argc="<< argc << endl;
    for(int i=1; i<argc; i++){
        input.open(argv[i]);
        if(!input){
            cout << "Error: input "<< argv[1] << " open failed!" << endl;
            return 1;
        }

        while(getline(input, str)){
            cout << i << ">" << str << endl;
        }
        //使用完关闭
        input.close();
    }

    return 0;
}

/*
$ g++ a10_open_close_open.cpp 
$ ./a.out a8_file.txt a8_file2.txt 
input a line: stop with ctrl+D
1>S1 4 20.1
1>S2 1 30.5
2>S1 40
2>S2 10
*/