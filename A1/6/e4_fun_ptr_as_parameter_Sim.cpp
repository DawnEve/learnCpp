#include<iostream>
using namespace std;

//函数指针可以作为参数，简化写法

bool lengthCompare(const string &s1, const string &s2){
    return s1.size() > s2.size();
}

bool lengthCompare2(const string &s1, const string &s2){
    return s1.size() < s2.size(); //和上一个相反
}

//简化函数指针的写法
typedef bool (*FunP)(const string&, const string&); //声明1
typedef decltype(lengthCompare) *FuncP2; //声明2

const string &useBigger(const string &s1, const string &s2, 
    FuncP2 pf){ //最后一个参数简化了
        return ( pf(s1, s2) ? s1 : s2 );
}

int main(){ //main函数没变
    string s1="hi,", s2="hello";

    // 获取长字符串
    cout << useBigger(s1, s2, lengthCompare) << endl;

    // 换一个比较函数: 获取短字符串
    cout << useBigger(s1, s2, &lengthCompare2) << endl; //加&fn 是可选的

    return 0;
}