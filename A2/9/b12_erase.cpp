#include<iostream>
#include<list>
using namespace std;

// c.erase(iter); 删除iter指向的元素，返回指向被删元素下一个位置的
int main(){
    list<int> lst={0,1,2,3,4,5};
    auto it=lst.begin();
    while(it != lst.end()){
        if( *it % 2)  //如果元素为奇数
            it = lst.erase(it); //则删除该元素
        else
            ++it;
    }

    // 打印结果
    for(auto i: lst)
        cout << i << " ";
    cout << endl;

    return 0;
}