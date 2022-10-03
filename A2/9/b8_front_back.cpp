#include<iostream>
#include<list>
using namespace std;

int main(){
    list<int> c={1, 6};
    //在解引用一个迭代器或者front或back前检查是否有元素
    if(!c.empty()){
        // val 和 val2 是c中第一个元素值的拷贝
        auto val=*c.begin(), val2=c.front();
        cout << val << ": " << &*c.begin() << ", " 
             << val2 << ": " << &c.front() << endl; //地址确实一样

        // val3和 val4 是c中最后一个元素值的拷贝
        auto last = c.end();
        auto val3=*(--last); //不能递减 forward_list 迭代器
        auto val4=c.back(); // forward_list 不支持
        cout << val3 << ": " << &*last << ", " 
             << val4 << ": " << &c.back() << endl; //地址确实一样
    }

    return 0;
}