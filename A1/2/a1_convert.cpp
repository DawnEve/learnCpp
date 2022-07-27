#include<iostream>
int main(){
    unsigned u=10;
    int i=-42;
    std::cout << "i+i=" << i+i << std::endl; //-84
    std::cout << "i+u=" << i+u << std::endl; //4294967264
    std::cout << "u+i=" << u+i << std::endl; //4294967264
    return 0;
}