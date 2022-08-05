#include<iostream>
using namespace std;

//多维数组，使用 begin 和 end 遍历, 更简洁
int main(){
    int arr[2][3]={ {1,2,3}, {10,20,30}};

    //p指向arr第一个数组
    for(auto p=begin(arr); p!=end(arr); ++p){
        //q指向内层数组的首元素
        for(auto q=begin(*p); q!=end(*p); ++q){
            cout << *q << "\t";
        }
        cout << endl;
    }

    return 0;
}