#include<iostream>
#include<vector>
using namespace std;

//在循环中改变容器
int main(){
    vector<int> vi={0,1,2,3,4,5};
    auto iter=vi.begin();  //调用begin 而不是 cbegin，因为我们要改变vi
    // 删除偶数元素，复制每个奇数元素
    while(iter != vi.end()) {
        if( *iter %2){ //如果是奇数
            iter = vi.insert(iter, *iter); //复制当前元素：在iter所指位置之前插入元素 *iter，返回新插入的元素位置
            iter+=2; //向前移动2，跳过新插入的元素和原 iter指向的元素
        }else{
            iter = vi.erase(iter); // 删除偶数元素：返回被删元素的下一个位置
        }
    }

    //打印
    for(auto i: vi)
        cout << i << " ";
    cout << endl; 
    
    return 0;
}