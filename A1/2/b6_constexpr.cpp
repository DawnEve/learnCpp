#include<iostream>
using namespace std;

int get_size(){
    return sizeof(int)*5;
}

int main(){
    // C++11
    constexpr int mf=20;
    constexpr int limit = mf+1;

    //constexpr int sz=get_size();
    // error: call to non-‘constexpr’ function ‘int get_size()’

    return 0;
}