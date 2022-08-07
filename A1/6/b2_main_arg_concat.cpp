#include<iostream>
using namespace std;

//从命令行获取2个参数，并连接成长字符串输出
int main(int argc, char *argv[]){
    int i=0;
    while(argv[i] !=0){
        i++;
    }
    if(i<2){
        cout << "Error: must provide 2 parameters" << endl;
        return -1;
    }

    string s1=argv[1];
    string s2=argv[2];
    cout << s1+s2 << endl;

    return 0;
}