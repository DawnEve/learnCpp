#include<iostream>
#include<array>
using namespace std;

//swap 没有交换元素，只是交换了容器的内部数据结构：array 是例外
int main(){
    array<string, 3> svect1={"hi", "how", "are"};
    array<string, 3> svect2={"this", "is", "book"};

    cout << "addr Bef: " << &svect1[2] << " " << &svect2[2] << endl;
    swap(svect1, svect2); // 对于array，swap后元素的地址不变，就是发生了拷贝
    cout << "addr Aft: " << &svect1[2] << " " << &svect2[2] << endl;

    for(auto i : svect1)
        cout << i << " ";
    cout << endl;

    return 0;
}