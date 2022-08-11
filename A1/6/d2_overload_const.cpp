#include<iostream>
using namespace std;

int lookup(int);
int lookup(const int); //重新声明了 int lookup(int)

int lookup(int *);
int lookup(int* const); //重新声明了 Record lookup(int *)


int arr[]={10,11,12,30,14,50};

int main(){
    int a2=12;
    int i2=lookup(a2);
    cout << "index of " << a2 << " is " << i2 << endl;

    return 0;
}

int lookup(int value){
    for(int i=0; i<6; i++){
        if(arr[i]==value)
            return i;
    }
    return -1;
}

/* 声明不报错，但是定义时报错
//error: redefinition of ‘int lookup(int)’
int lookup(const int value){
    return -1;
}
*/