#include<iostream>
using namespace std;

int get_size(){
    return sizeof(int)*5;
}

int main(){
    const int max_files=20;  // max_files 是常量表达式
    const int limit = max_files +1; // limit 是常量表达式
    
    int staff_size=27; //staff_size不是常量表达式：数据类型是int，而不是 const int
    const int sz=get_size(); //sz 不是常量表达式：尽管是常量，但是数值需要运行时才能获取到

    return 0;
}