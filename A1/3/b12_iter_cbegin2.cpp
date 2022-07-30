#include<iostream>
#include<string>
#include<vector>
using namespace std;

// fix: char 没有 empty 方法。需要把 text 改为 vector<string> 类型
int main(){
    vector<string> text={"this is a book.", "hello, c++"};
    //使用迭代器遍历读，直到遇到空格停止
    for(auto it=text.cbegin();
        it != text.cend() && !it->empty(); 
        //it != text.cend() && (*it).empty(); 
        ++it){
        cout << *it << "\n";
    }
    cout << endl;

    return 0;
}