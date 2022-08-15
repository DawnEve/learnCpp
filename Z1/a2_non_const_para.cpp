#include<iostream>
#include<vector>
using namespace std;

/*
void push_back (const value_type& val);
如果没有const，vec.push_back(5)这样的代码就无法编译通过了
*/

vector<int> arr={0,1,2,3};

//void push_back (const int & val){
void push_back (int & val){ //右值引用无法传入
    arr.push_back(val);
}

int main(){
    int x=10;
    push_back(x);
    //push_back(5); //error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    
    for(auto i: arr)
        cout << i << " ";
    cout << endl;

    return 0;
}