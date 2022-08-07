#include<iostream>
using namespace std;

// initializer_list 获取不定数量参数，类型相同
void error_msg(initializer_list<string> il){
    for(auto beg=il.begin(); beg!=il.end(); ++beg){
        cout << *beg << " ";
    }
    cout << endl;
}


int main(){
    //测试错误信息
    string expected="hello";
    string actual;
    cout << "Please input hello, other word may produce an error message:" << endl;
    cin >> actual;

    if(expected != actual){
        error_msg({"functionX error:", expected, actual}); //注意，字符串要写到花括号中
    }else{
        error_msg({"functionX", "okey"}); //第一次调用传入3个值，第二次调用传入2个值
    }

    return 0;
}