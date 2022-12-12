#include<iostream>
#include <functional>
using namespace std;

// 函数返回 lambda 的写法
// https://stackoverflow.com/questions/4726768/function-returning-a-lambda-expression

// 定义2个lambda
auto bigger =[](int a, int b) ->int{ if(a>b) return a; return b;};
auto smaller=[](int a, int b) ->int{ if(a<b) return a; return b;};

// 方法1: 函数返回一个 lambda，输入是(int,int)，返回是 int
function<int(int, int)> fn(int value){
    if(value>0) return bigger;
    return smaller;
}
// test
void demo1(){
    int x=10, y=20;
    //cout << bigger(x, y) << endl;
    //cout << smaller(x, y) << endl;
    
    cout << fn(1)(x, y) << endl;
    cout << fn(-1)(x, y) << endl;

    // 对于函数 fn == *fn; fn == &fn;
    cout << (fn == *fn) << endl; //1
    cout << (fn == &fn) << endl; //1
}


// 方法2: 使用 typedef，有函数的返回值
typedef int (*identity_t)(int, int); // works with gcc 
// 函数指针的定义方法，前面加上 typedef, 把函数名替换为(*ptrName) 即可
identity_t fn2(int value){
    if(value>0) return bigger;
    return smaller;
}
void demo2(){
    int x=10, y=20;
    cout << "fn2: " << fn2(1)(x, y) << endl;
    cout << "fn2: " << fn2(-1)(x, y) << endl;

    cout << "&bigger:" << &bigger << "\t" << "&fn2(1):" << (void *)fn2(1) << endl;
}

// todo: 函数返回一个 lambda 的引用
/*
function<int(int, int)>&& fn3(int value){
    if(value>0) return &bigger;
    return &smaller;
}

void demo3(){
    int x=10, y=20;
    cout << fn3(1)(x, y) << endl;
}
*/

int main(){
    demo1(); printf("\n");
    demo2(); printf("\n");
    //demo3();
    return 0;
}