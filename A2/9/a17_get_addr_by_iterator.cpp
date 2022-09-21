#include<iostream>
#include<vector>
#include<list>
using namespace std;

// 通过迭代器获取元素的地址
/*不能直接取迭代器的地址
对迭代器加*，即获得该迭代器所指的元素
对迭代器加*，再加&，就是该元素的地址 */
int main(){
    vector<int> arr1={1,2,3};
    list<int> l2={-1,-2,-3};

    // 一个元素只占用4位
    auto be1=arr1.begin();
    while(be1 != arr1.end()){
        cout << &*be1 << ": " << *be1 << endl;
        be1++;
    }
    cout << endl;

    // list 确实很消耗内存，一个元素占用 f00-ee0 = 32位 = 4+8+8+?: 一个int是4,2个指针是2*8，还有 12 是啥占用的？
    auto be2=l2.begin();
    while(be2 != l2.end()){
        cout << &*be2 << ": " << *be2 << endl;
        be2++;
    }
    cout << endl;
    cout << 0xf00 - 0xee0 << endl;

    return 0;
}