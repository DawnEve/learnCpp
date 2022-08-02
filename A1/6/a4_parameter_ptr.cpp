#include<iostream>
using namespace std;

// 指针形参
void change(int *p){
    *p *= 2; //指针指向的整数值 改变，指针实参不变
}

void change2(int *p){
    p=0; // 指向的整数值不变，指针实参也不变。
}

int main(){
    int i=1024;
    int *ptr=&i;
    cout << "1 ptr=" << ptr << ", value *ptr=" << *ptr <<  endl;

    // change value
    change(ptr);
    cout << "2 ptr=" << ptr << ", value *ptr=" << *ptr <<  endl;

    //change 2
    change2(ptr);
    cout << "3 ptr=" << ptr << ", value *ptr=" << *ptr <<  endl;

    return 0;
}