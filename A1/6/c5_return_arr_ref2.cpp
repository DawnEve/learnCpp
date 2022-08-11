#include<iostream>
using namespace std;

//返回数组引用的函数，该数组包含3个 string 对象

string arr0[]={"nothing", "here", "now"};
string arr1[]={"how", "are", "you"};

//0.直接声明
//string (&getRef)(int index)[3]; //error: ‘getRef’ declared as function returning an array
//string (&getRef(int index))[3];

//其他3种声明形式：类型别名、尾置返回类型、decltype关键字

//1. 类型别名
//typedef string ref_str4[3];
//using ref_str4 = string [3];

//ref_str4 &getRef(int i);


//2. 尾置返回类型
//auto getRef(int i) -> string (&)[3];

//3.decltype关键字
decltype(arr0) &getRef(int i);

int main(){
    cout << 3 << endl; //显式表示变化
    cout << arr0 << endl;
    cout << arr1 << endl;

    for(int i=0; i<2; i++){
        cout << getRef(i) << "\t" << getRef(i)[0]  << endl;
    }
    return 0;
}

string (&getRef(int n))[3]{
    if(n==0)
        return arr0;
    else
        return arr1;
}