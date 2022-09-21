#include<iostream>
#include<vector>
using namespace std;

//swap 没有交换元素，只是交换了容器的内部数据结构(array 除外)
int main(){
    vector<string> svect1(10);  //10个元素的string
    vector<string> svect2(24);  //24个元素的string

    cout << "addr Bef: " << &svect1[2] << " " << &svect2[2] << endl;
    swap(svect1, svect2);
    cout << "addr Aft: " << &svect1[2] << " " << &svect2[2] << endl;

    cout << svect1.size() << endl;
    cout << svect2.size() << endl;

    return 0;
}