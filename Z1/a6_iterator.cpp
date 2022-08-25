#include<iostream>
#include<vector>
using namespace std;
// 函数: vector.erage(iter); //删除iter指向的元素，返回指向下一个元素的迭代器
void print(vector<int> &v); //输出数组

//目的：未知。猜测可能是删除连续的重复元素
void removeConsecutiveRep(vector<int> &v){
    vector<int>::iterator be=v.begin(), ed=v.end();
    int i=*(be++); //取值第一个元素，并指向第二个
    while( be < ed ){
        if( *be == i){
            be = v.erase(be); //删除该元素，指向下一个
            ed=v.end();  //再获取end，因为vector长度缩短了
        }else{
            i = *(be++);
        }
    }
}

int main(){
    vector<int> arr={1,2,2,3,4, 4,4,4,4,4,4,4, 5,6,7,8,  8,8};
    //vector<int> arr={1,1,1,1,2,1,3,3,3,4};
    cout << ">>len:" << arr.size() << endl;
    print(arr);

    removeConsecutiveRep(arr);// 去重:连续的只保留1个
    
    cout << ">>len:" << arr.size() << endl;
    print(arr);
    return 0;
}


void print(vector<int> &v){
    vector<int>::iterator begin=v.begin(), end=v.end();
    for(; begin!=end; begin++)
        cout << *begin << " ";
    cout << endl;
}