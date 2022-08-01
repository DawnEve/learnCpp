#include<iostream>
#include<cstring>
using namespace std;

// 字符串的比较
int main(){
    //1.标准库 string 类型比较
    string s1="a small dog;";
    string s2="a small cat;";

    if(s1 > s2)
        cout << s1 << " is > " << s2 << endl;
    
    //2. C 风格字面量的比较
    const char c1[]="A big dog;";
    const char c2[]="A big cat;";

    //(1) 
    if(c1 > c2) //实际比较的是2个指针，而非字符串本身
        cout << c1 << " is > " << c2 << endl;
    else
        cout << " c1> c2, else" << endl;

    //(2)相比较C风格的字符串，需要用 strcmp 函数
    if( strcmp(c1, c2)>0 ){
        cout << c1 << " is > " << c2 << endl;
    }

    return 0;
}