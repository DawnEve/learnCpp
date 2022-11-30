#include<iostream>
using namespace std;

int main(){
    //拷贝内置数组：copy
    int a1[]={1,2,3}, len=sizeof(a1)/sizeof(*a1);
    int a2[len];

    // print
    for(auto ele: a2)
        cout << ele << " ";
    cout << endl;

    // copy
    auto ret=copy(begin(a1), end(a1), a2); // 把a1的内容拷贝给a2
    printf("&a1=%p, &a2=%p, &*ret=%p ret=%p\n", a1, a2, &*ret, ret);

    // print
    for(auto ele: a2)
        cout << ele << " ";
    cout << endl;

    cout << *(--ret) << endl;

    return 0;
}