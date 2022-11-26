#include<iostream>
#include<iterator>
#include<vector>

using namespace std;

void demo1(){
    vector<int> vec={1,2,3};

    fill_n(vec.end()-1, 3, 100); //插入3个元素，每个值是100。结果后面只有1个位置，没有的位置插入失败
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl; 
}

void demo2(){
    vector<int> vec={1,2,3};

    auto it= back_inserter(vec);
    fill_n( it, 3, 100); //插入3个元素，每个值是100。成功
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl; 
}


int main(){
    demo1();
    demo2();
    return 0;
}