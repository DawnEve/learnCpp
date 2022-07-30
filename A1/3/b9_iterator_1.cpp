#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> iVec(5, 0); //5个元素，值都是0(可省略)
    for(int i=0; i<iVec.size(); i++)
        iVec[i]=i; //赋值 [0, 4]

    //b表示第一个元素，e表示最后一个元素
    auto b=iVec.begin(), e=iVec.end(); //类型由编译器确定

    cout << *b << endl; // *iter 返回迭代器所指元素的引用
    cout << *(--e) << endl; //尾元素的下一个位置，往上移1，就是最后一个元素
    return 0;
}