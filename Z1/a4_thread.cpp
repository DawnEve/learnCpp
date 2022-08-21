#include<iostream>
#include<thread>
using namespace std;

// 多线程
//https://www.runoob.com/cplusplus/cpp-multithreading.html
void f1(int n){
    while(n-- >0){
        printf(">> f1()%d\n", n);
    }
}

class Book{
public:
    void operator()(int x){
        while(x-- >0){
            //cout << "Book()" << x << endl;
            printf("Book()%d\n", x);
        }
    }
};

int main(){
    thread th1( Book(), 10); // 函数对象
    thread th2( f1, 10); // 函数指针

    // 等待线程完成
    th1.join();// 等待线程 t1 完成    
    th2.join();// 等待线程 t2 完成

    return 0;
}

//g++ -std=c++11 a4_thread.cpp -lpthread