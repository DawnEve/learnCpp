#include<iostream>
#include<stack>
#include<vector>
#include<string>

using namespace std;

// 适配器的第二个参数：类型参数

int main(){
    vector<string> svec={"this", "is", "a", "book"};
    //在 vector 上实现的空栈
    stack<string, vector<string>> str_stk;

    // str_stk2 在 vector 上实现，初始化时保存 svec 的拷贝
    stack<string, vector<string>> str_stk2(svec);

    //打印栈: 先进的后出
    while(!str_stk2.empty()){
        string val=str_stk2.top(); //获取顶端的值
        str_stk2.pop(); //删掉顶端的值
        cout << val << endl;
    }

    return 0;
}