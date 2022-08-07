#include<iostream>
using namespace std;

//返回局部变量的值的引用，也会报错
const string &manip(int signal){
    string ret;
    // 改变一下rect的值
    if(signal==0)
        ret =0;
    else
        ret="hi";
    
    if( ! ret.empty() )
        return ret;  //错误：返回局部对象的引用
        // warning: reference to local variable ‘ret’ returned
    else
        return "Empty"; //错误："Empty" 是一个局部临时量
        // warning: returning reference to temporary
}


int main(){
    const string s0=manip(0);
    const string s1=manip(1);

    //cout << s0 << endl;
    //cout << s1 << endl;

    return 0;
}