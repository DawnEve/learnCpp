#include<iostream>
using namespace std;

//使用迭代器遍历数组： begin end
int main(){
    int arr[3]={10, 11, 12};
    // C++11 新引入的函数 begin 和 end，返回的指针：首位置和尾后
    int *beg=begin(arr);
    int *last=end(arr); //变量名不能和函数名同名(这里使用 last)，否则报错 ‘end’ cannot be used as a function

    int i=0;
    for(; beg != last; ++beg){
        cout << *beg;
        cout << "\t" << beg << " " << &arr[i] << " " << arr[i] << endl;
        i++;
    }
    return 0;
}