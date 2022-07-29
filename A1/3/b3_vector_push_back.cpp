#include<iostream>
#include<vector>
using namespace std;

int main(){
    // v.push_back(item) 在v的末尾添加元素item
    vector<int> ivec; //空vector对象
    cout << "length:" << ivec.size() << endl;

    for(int i=0; i<=5; i++){
        ivec.push_back(i); //把每个i放到ivec的末尾
    }
    cout << "length:" << ivec.size() << endl;

    //输出
    for(int i=0; i<ivec.size(); i++)
        cout << i << " " << ivec[i] << endl;
    
    return 0;
}