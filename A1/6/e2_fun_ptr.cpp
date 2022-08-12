#include<iostream>
using namespace std;

//函数指针，只识别形参和返回值，不识别函数名

bool lengthCompare(const string &s1, const string &s2){
    cout << __func__ << endl;
    return s1.size() > s2.size();
}

bool cmpFirstString(const string &s1, const string &s2){
    cout << __func__ << endl;
    return s1[0] > s2[0];
}

int totalSize(const string &s1, const string &s2){
    return s1.size() + s2.size();
}

bool (*pf)(const string&, const string &);

int main(){
    string x="hello", y="Anderson";
    pf=lengthCompare;
    cout << pf(x, y) << endl;

    pf=&cmpFirstString;
    cout << pf(x, y) << endl;

    //pf=totalSize; 
    //error: invalid conversion from ‘int (*)(const string&, const string&)’ to ‘bool (*)(const string&, const string&)’

    return 0;
}