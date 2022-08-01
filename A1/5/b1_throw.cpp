#include<iostream>
using namespace std;

// 抛出异常
int main(){
    int a, b;
    cout << "Please input 2 int:" << endl;
    cin >>a >> b;
    if(b==0){
        throw runtime_error("must not be devided by 0");
    }

    //如果执行到这里，说明b不等于0
    cout << a/b << endl;
    
    return 0;
}