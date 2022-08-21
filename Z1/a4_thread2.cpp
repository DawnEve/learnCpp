#include<iostream>
#include<thread>
using namespace std;

// 多线程2: 类内多线程，只能是静态方法吗？
//g++ -std=c++11 a4_thread2.cpp -lpthread

void f1(int n){
    while(n-- >0){
        printf(">> f1()%d\n", n);
    }
}

class Book{
public:
    int i; //默认初始化随机值
    void operator()(int x){
        while(x-- >0){
            //cout << "Book()" << x << endl;
            printf("Book()%d\n", x);
        }
    }

    static void bf1(int x){
        while(x-- >0)
            printf("Book::bf1()%d\n", x);
    }
    static void bf2(int x){
        while(x-- >0)
            printf(">> Book::bf2()%d\n", x);
    }
    void test(){
        thread th1( bf1, 10); // 函数对象
        thread th2( bf2, 10);

        // 等待线程完成
        th1.join();// 等待线程 t1 完成    
        th2.join();// 等待线程 t2 完成
    }
};

int main(){
    Book book;
    book.test();

    cout << book.i << endl;
    return 0;
}