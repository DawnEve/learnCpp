#include<iostream>
#include<string>
#include <unistd.h>
using namespace std;

// 进度条: 原生实现

int main(){
    int total=80;
    float ratio=0;
    string row=" ";
    // 百分比数字前的空格
    for(int i=0; i<=total; i++){
        row += " ";
    }

    // 显示进度条
    for(int i=0; i<=total; i++){
        string str="";
        ratio = (1.00*i)/total * 100;
        for(int j=0; j<i; j++){
            str += "=";
        }
        //1. sleep for some us; https://www.gaojiufeng.cn/?id=301
        usleep(0.05*1e6);
        //printf("%s>>\r", str.c_str() );
        //2. 只刷新缓存不换行 https://www.likecs.com/ask-152700.html
        cout << row << (int)ratio << "%\r"; 
        cout << str << "=>\r" << std::flush; 
    }
    //换行
    cout << endl;
    return 0;
}