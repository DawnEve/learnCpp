#include<iostream>
#include<vector>
using namespace std;

// 关系运算符
int main(){
    vector<int> v1={1,3,5,7,9,12};
    vector<int> v2={1,3,9};
    vector<int> v3={1,3,5,7};
    vector<int> v4={1,3,5,7,9,12};
    cout << (v1<v2) << endl; //true; 第一个不等的元素 5<9
    cout << (v1<v3) << endl; //false: 已有元素都相等，但是v1长
    cout << (v1==v4) << endl; //true：每个元素都相等
    cout << (v1==v2) << endl; //false: 数目不等

    return 0;
}