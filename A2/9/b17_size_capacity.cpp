#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> ivec;
    //size 应该是0； capacity 的值依赖于具体实现
    cout << "1 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;
        
    // 添加24个元素
    for(vector<int>::size_type ix=0; ix!=24; ++ix){
        ivec.push_back(ix);
    }
    // size 应该是24； capacity 的值依赖于具体实现
    cout << "2 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;
    

    // 请求分配更多空间
    ivec.reserve(50);
    // size 应该是24； capacity 的值依赖于具体实现，应该大于等于50
    cout << "3 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;
    

    // 添加元素，用完剩余空间
    while( ivec.size() != ivec.capacity() )
        ivec.push_back(0);
    // capacity 应该未改变
    cout << "4 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;

    // 再添加1个元素，vector 就不得不重新分配内存空间了
    ivec.push_back(1);
    // capacity 应该未改变
    cout << "5 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;
    
    //可以采用 shrink_to_fit 要求 vector 退回多余的空间给系统
    ivec.shrink_to_fit();
    cout << "6 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;
    return 0;
}