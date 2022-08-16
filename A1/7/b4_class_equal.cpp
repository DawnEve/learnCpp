#include<iostream>
using namespace std;

class A{};
class B{};

int main(){
    A a1;
    B b1=a1;
    // error: conversion from ‘A’ to non-scalar type . requested

    return 0;
}