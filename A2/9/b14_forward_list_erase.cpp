#include<iostream>
#include<forward_list>
using namespace std;

int main(){
    forward_list<int> flst={0,1,2,3,4,5};
    auto prev=flst.before_begin(); //第一个元素之前的位置
    auto curr=flst.begin(); //第一个元素

    while( curr != flst.end() ){
        if(*curr % 2)  //当前元素是奇数
            curr=flst.erase_after(prev);  //则删掉，使用其前的迭代器
        else{
            //不是奇数，则2个迭代器都向后移动：前=当前，当前后移
            prev=curr; 
            ++curr;
        }
    }
    //打印结果
    for(auto i: flst)
        cout << i << " ";
    cout << endl;

    return 0;
}