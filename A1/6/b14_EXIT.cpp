#include<iostream>
using namespace std;

int main(int argc, char **argv){
    int i=argc;
    cout << "Parameter number: " << i-1 << endl;

    //不输入参数则报错
    if(i>1){
        cout << "ok" << endl;
        return EXIT_SUCCESS; //定义在 cstdlib 头文件中
    }else{
        cout << "Error: no parameter" << endl;
        return EXIT_FAILURE; //定义在 cstdlib 头文件中
    }
}