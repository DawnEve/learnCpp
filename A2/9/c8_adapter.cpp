#include<iostream>
#include<deque>
#include<stack>
using namespace std;

void demo1(){
    //定义一个容器
    deque<int> deq={1,2,30,40};
    for(auto i: deq){
        cout << i << endl;
    }
    cout << endl;

    // 栈：先进后出
    stack<int> stk(deq); //从deq拷贝元素到stk
    while(!stk.empty()){
        int val=stk.top(); //获取顶端的值
        stk.pop(); //删掉顶端的值
        cout << val << endl;
    }
}

int main(){
    demo1();
}