#include<iostream>
using namespace std;

// 如果参数是指针或引用，则通过区分其指向的是常量还是非常量对象，可以实现函数重载
int lookup(int&);  //输入int的引用
int lookup(const int&); //新函数，作用于常量引用

int lookup(int *); //作用于指向int的指针
int lookup(const int *); //作用于指向 const int 的指针


int arr[]={10,11,12,30,14,50};

int main(){
    int a1=12, &r1=a1, *p1=&a1;
    int i1=lookup(r1);
    cout << "1 index of " << r1 << " is " << i1 << endl;

    const int &r2=a1;
    int i2=lookup(r2);
    cout << "2 index of " << r2 << " is " << i2 << endl;

    int i3=lookup(p1);
    cout << "3 index of " << *p1 << " is " << i3 << endl;

    const int *p2=&a1;
    int i4=lookup(p2);
    cout << "4 index of " << *p2 << " is " << i4 << endl;

    return 0;
}

int lookup(int &r){
    return -11;
}

int lookup(const int &r){
    return -12;
}


int lookup(int *p){
    for(int i=0; i<6; i++){
        if(arr[i]==*p)
            return i;
    }
    return -1;
}

int lookup(const int *p){
    return -14;
}
