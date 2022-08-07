#include<iostream>
using namespace std;

//main 函数接受参数
int main(int argc, char **argv){
    // 打印各个参数
    cout << "argc=" << argc << endl;
    
    int i=0;
    while (argv[i] != 0){
        cout << "argv[" << i << "]=" << argv[i] << endl;
        i++;
    }
    cout << endl;

    while (*argv != 0){
        cout << "*argv=" << *argv++ << endl;
    }

    return 0;
}