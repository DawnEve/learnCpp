#include<iostream>
using namespace std;

int main(){
    // 取成员变量，使用点或者箭头都是可以的
    string s1="this is a book", *p=&s1;
    auto n=s1.size(); //运行 string 对象 s1 的 size 成员函数

    cout << (*p).size() << endl;
    cout << p->size() << endl;

    // 圆括号必须有
    //cout << *p.size() << endl; //因为解引用的优先级低于点，指针没有点运算，报错
    //  error: request for member ‘size’ in ‘p’, which is of pointer type ‘std::string*’ 
    // {aka ‘std::__cxx11::basic_string<char>*’} (maybe you meant to use ‘->’ ?)

    return 0;
}