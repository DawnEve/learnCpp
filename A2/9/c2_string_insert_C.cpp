#include<iostream>
using namespace std;

// 接受C风格的字符串数组
int main(){
    string s="this is a book";
    cout << "1 " << s << endl;

    const char *cp="hello, world!";
    s.assign(cp, 7); // 获取cp前7个字符，覆盖到s上
    cout << "2 " << s << endl;

    // 插入：要插入的位置，指向新字符串的指针位置
    s.insert(s.size(), cp+7); //结尾不存在的字符之前插入字符串 cp+7 的拷贝
    cout << "3 " << s << endl;

    //插入开头
    string s2="NEW BOOK.";
    s.insert(0, s2); //在0位置之前插入字符串s2的拷贝
    cout << "4 " << s << endl;

    // 在s开头之前，插入s2[0]开始到 s2.size()-1个字符
    string s3="a fox";
    s.insert(0, s3, 0, s3.size()-1 );
    cout << " s3.size()=" << s3.size() << endl;
    cout << "5 " << s << endl;
}