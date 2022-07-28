#include<iostream>
using namespace std;

int main(){
    // 注意 int* i=1, j=2; 其实 *只管到i变量。
    int *ptr=nullptr, i=1024, &ref=i;
    ptr=&i;
    cout << "   i=" << i << endl;
    cout << " ref=" << ref << endl;
    cout << "*ptr=" << *ptr << endl;
    return 0;
}