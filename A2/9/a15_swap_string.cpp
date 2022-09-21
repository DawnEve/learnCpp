#include<iostream>
#include<vector>
using namespace std;

// swap 两个 string 会使迭代器失效?? 我的测试不失效。
void test1(){
    string s1="hi", s2="this";
    auto be=s1.begin();
    cout << "befor: s1:" << *be << ", &s1:" << &s1 << endl;
    //swap(s1, s2);
    s1.swap(s2); //同上
    cout << "after: s1:" << *be << ", &s1:" << &s1 << endl; //没有变，只不过
    cout << s1 << endl;
}


// swap vector 看迭代器指向：交换内部数据结构，时间 常数
void test2(){
    cout << ">> test2" << endl;
    vector<int> l2={0,10};     //名字提示原始长度信息
    vector<int> l3={-1,-2,-3};
    auto be=l2.begin(), end=l2.end();
    while(be != end){
        cout << *be << ", &be:" << &be << endl;
        be++;
    }
    be=l2.begin();

    cout << l2.size() << "| befor: l2:" << *be << ", &l2[1]:" << &l2[1] << ", val:" << l2[1] << endl;
    swap(l2, l3);
    cout << l2.size() << "| after: l2:" << *be << ", &l2[1]:" << &l2[1] << ", val:" << l2[1] << endl;

    //如果是 list<int> 则无法结束? 为什么？说明一对迭代器被破坏了？
    int i=0;
    while(be != end){
        cout << i << ">> " << *be << ", &be:" << &l2 << endl;
        be++;
        if(++i > 9)
            break;
    }
}


int main(){
    test1();
    test2();
}