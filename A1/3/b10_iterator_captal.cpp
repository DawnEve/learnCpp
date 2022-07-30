#include<iostream>
#include<string>
using namespace std;

int main(){
    string s2("hello c++");
    cout << "&s2=" << &s2 << endl;
    char &ref=s2[0];
    //cout << "s2[0]=" << s2[0] << ", &(s2[0])=" << &(s2[0]) << endl;
    cout << "s2[0]=" << s2[0] << ", ref=" << ref << ", &ref=" << &ref << endl;
    if( s2.begin() != s2.end()){ //确保非空
        auto it = s2.begin(); //it 指向s2的第一个首字母
        *it = toupper(*it);
        cout << "&it=" << &it << ", *it=" << *it << endl;
    }
    // 输出结果
    cout << s2 << endl;
    return 0;
}

// 字符串首字符的地址，和指向第一个字符迭代器不一样，正好差了16