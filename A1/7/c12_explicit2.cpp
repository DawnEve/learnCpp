#include<iostream>
using namespace std;

// 发生隐式类型转换，如果是拷贝形式（使用=号），
//则只能使用直接初始化，不能使用explicit构造函数

class Book{
private:
    string ISBN;
public:
    explicit Book(string s1): ISBN(s1){}
    void show(){cout << ISBN << endl;}
};

int main(){
    string s2="9-99";
    Book book1(s2); //正确，直接初始化
    //Book book2 = s2; //错误：不能将explicit构造函数用于拷贝形式的初始化过程
    //error: conversion from ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’} to non-scalar type ‘ requested

    book1.show();
    return 0;
}