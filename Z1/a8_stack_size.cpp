#include<iostream>
using namespace std;


// 测试 ubuntu 的栈有多大？ //todo 未实现。思路：可能要借助于递归函数的报错来实现调用了多少层
// ulimit -s 直接查
struct Book{
    long num1;
    long num2;
};

void test1(){
    long a=1;
    cout << sizeof(long) << endl;
    cout << 1.00*sizeof(long) * 2* 100000*5 / 1024/1024 << "Mb" << endl;

    // part 2
    Book arr1[100000], arr2[100000], arr3[300000];

    int i=0;
    for(i=0; i<30000; i++){
        arr3[i].num1 = arr1[i].num1 + arr2[i].num1;
        arr3[i].num2 = arr1[i].num2 + arr2[i].num2;
        if(i % 1000==0)
            cout << i << "; &arr3[i]=" << &arr3[i] << endl;
    }
    cout << "end: " << i << endl;
}

void test2(){
    typedef unsigned char Byte; 
    //Byte *pb=new Byte[1024*50];
    //long len= 100000*5; //same as test1&2
    long len= 100000*10;
    Book *pb=new Book[len];
    pb[1000].num1=125;
    cout << 1.000* sizeof( long ) * 2* len /1024/1024 << "M" << endl;
    
    for(long i=0; i< 30000; i++){
        if(i %1000==0)
            cout << "pb["<<i<<"].num1="<< pb[i].num1 <<endl;
    }
    free(pb);
}


// gcc -Wl,–stack=栈尺寸
//例如 gcc -Wl,–stack=0x4000000
int main(){
    // ==> in stack
    //test1();

    // ===> in heat
    test2();

    // ==> use recur fun //todo

    return 0;
}