#include<iostream>
using namespace std;

void demo1(){
    //反例1: insert 使用下标+初始化列表参数
    string s1="hi";
    s1.insert(2, {", world!"});
    cout << "1 " << s1 << endl; //1 hi, world!
}
void demo2(){
    //例子2: insert 使用迭代器 + c风格字符串参数，报错
    string s2="hello, ";
    char cp[]="this is g++"; //定义C风格字符串
    printf("cp=%s\n", cp);

    //A: 参数1为迭代器时
    //s2.insert(s2.begin(), cp);
    //s2.insert(s2.end(), cp); //n: 找不到对应的重载函数 error: no matching function for call to...
    //s2.insert(s2.end(), *cp); //y1.可以插入单个字符  2 hello, t

    string s3=string(cp) + " book";
    s2.insert(s2.end(), s3.begin(), s3.end() ); //y2.参数2可以是两个迭代器，不能指向调用者

    //B: 参数1为下标时
    //s2.insert(s2.size(), cp ); //参数2使用C风格字符串
    //s2.insert(s2.size(), string(cp) ); //参数2位string对象
    
    cout << "2 " << s2 << endl;
}


int main(){
    //demo1();
    demo2();
}