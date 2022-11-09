#include<iostream>
#include<stack>
using namespace std;

//栈 适配器
int main(){
    stack<int> intStack; //空栈
    // 填满栈
    for(size_t ix=0; ix!=5; ++ix){
        intStack.push(ix); //保存0-4共5个整数
    }

    //打印结果
    while(!intStack.empty()){
        int value=intStack.top(); //获取顶部元素
        intStack.pop();  //弹出栈顶元素，没有返回值
        cout << value << " ";
    }
    cout << endl;

    return 0;
}