#include<iostream>
using namespace std;

//返回数组引用的函数，该数组包含3个 string 对象
string arr0[]={"nothing", "here", "now"};
string arr1[]={"how", "are", "you"};

//string (&getRef)(int index)[3]; //error: ‘getRef’ declared as function returning an array
string (&getRef(int index))[3];

int main(){
    cout << arr0 << endl;
    cout << arr1 << endl;

    for(int i=0; i<2; i++){
        cout << getRef(i) << "\t" << getRef(i)[0]  << endl;
    }
    return 0;
}

string (&getRef(int n))[3]{
    if(n==0)
        return arr0;
    else
        return arr1;
}