#include<iostream>
using namespace std;

//函数指针可以作为参数

bool lengthCompare(const string &s1, const string &s2){
    return s1.size() > s2.size();
}

bool lengthCompare2(const string &s1, const string &s2){
    return s1.size() < s2.size(); //和上一个相反
}

const string &useBigger(const string &s1, const string &s2, 
    bool (*pf)(const string&, const string&)){
        return ( pf(s1, s2) ? s1 : s2 );
}

int main(){
    string s1="hi", s2="hello";

    //获取长的字符串
    const string &x1=useBigger(s1, s2, lengthCompare);
    cout << x1 << endl;
    cout << &x1 << "\t" << &s2 << endl;

    // 换一个比较函数
    cout << useBigger(s1, s2, &lengthCompare2) << endl; //加&fn 是可选的

    return 0;
}