#include<iostream>
#include<list>
using namespace std;

int main(){
    list<int> c={0,2,4};
    if(!c.empty()){
        c.front() = 12; //将12赋值给第一个引用
        
        auto &v=c.back(); //获取最后一个元素的引用
        v=1024; //改变最后一个元素的值
        auto v2=c.back(); //v2不是一个引用，它是c.back() 的一个拷贝
        v2=0; //未改变c中的元素

        for(auto i: c)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}