#include<iostream>
using namespace std;

//#define NDEBUG 使用这句定义，或者编译时参数 -D NDEBUG，都能使 #ifndef #endif之间的语句失效

// NDEBUG 编写调试语句
void print(const int ia[], size_t size){
    #ifndef NDEBUG
      // __func__ 是编译器定义的一个局部静态变量，用于存放函数的名字
      cerr << __func__ << ": array size is " << size << endl;
    #endif
    cout << "from func: " << __func__ << endl;
}

int main(){
    int arr[]={0,1,2,3}, size=sizeof(arr)/sizeof(int);
    print(arr, size);
    return 0;
}