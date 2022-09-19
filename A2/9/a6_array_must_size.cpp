#include<iostream>
#include<array>
using namespace std;

// 声明 array 时，除了元素类型，还必须指定容器大小
array<int, 10> arr0; //全局变量，自动初始化: 全为0

int main(){
    for(auto i: arr0)
        cout << i << "  ";
    cout << endl;

    array<int, 10> arr; //函数内，栈区不初始化: 是内存原来的值

    cout << "part II" << endl;
    for(auto i: arr)
        cout << i << "  ";
    cout << endl;

    return 0;
}