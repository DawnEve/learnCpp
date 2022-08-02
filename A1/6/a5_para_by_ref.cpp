#include<iostream>
using namespace std;

//按引用传递
void change(int &ref){
    ref *= 2; //改变了 ref 所引用的对象
}

int main(){
    int num=10;
    cout << num << endl;
    
    change(num);
    cout << num << endl;
    
    return 0;
}