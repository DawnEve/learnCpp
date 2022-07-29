#include<iostream>
#include<vector>
using namespace std;

// 初始化 vector 对象的方法
int main(){
    vector<int> v1;  //v1 是一个空vector，它的潜在元素是int类型，执行默认初始化
    vector<int> v2(v1); //v2 中包含 v1的所有元素的副本
    vector<int> v2_2=v1; //等价于 v2(v1) ，v2 中包含v1所有元素的副本
    vector<int> v3(5, 12); //v(n, val) v3包含n个重复的元素，每个元素的值都是val
    vector<int> v4(5); //v(n) v4中包含了n个执行了值初始化的对象
    vector<int> v5{1,2,3,10}; //v(a,b,c...)  v5包含了初始值个数的元素，每个元素被赋予相应的初始值
    vector<int> v5_2={1,2,3,20}; //等价于 v(a,b,c...)
    
    vector<vector<int>> iVec2;
    return 0;
}