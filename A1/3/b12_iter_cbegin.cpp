#include<iostream>
#include<string>
using namespace std;

int main(){
    string text="this is a book.";
    //使用迭代器遍历读，直到遇到空格停止
    for(auto it=text.cbegin();
        //it != text.cend() && !it->empty(); 
        it != text.cend() && (*it).empty(); 
        ++it){
        cout << *it << endl;
    }

    return 0;
}