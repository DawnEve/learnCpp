#include<iostream>
using namespace std;

//使用C++11新标准 auto 和 decltype ，可避免在数组前面加上一个指针类型
int main(){
    int ia[3][4]={1,2,3,4,5,6,7,8,9,10,11,12};
    // C++11 输出二维数组，每个内存元素一行
    for(auto p=ia; p!=ia+3; ++p){
        //q 指向4个整数数组的首元素，也就是说，q指向一个整数
        cout << ">>" << p << " | " << *p << endl;
        for(auto q=*p; q!=*p+4; ++q){ //必须解引用，虽然解引用后地址不变 //todo
            cout << *q << "|" << q << "\t";
        }
        cout << endl;
    }

    return 0;
}