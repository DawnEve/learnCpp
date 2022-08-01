#include<iostream>
#include<vector>
using namespace std;

//使用数组初始化 vector
int main(){
    int arr[]={0,1,2,3,4,5};

    //2个初始化 vector，分别是数组的头指针和尾后指针
    vector<int> ivec(begin(arr), end(arr));
    
    //遍历1
    for(auto i : ivec)
        cout << i << " ";
    cout << endl;

    // 使用其他指针初始化 vector: arr[1], arr[4]
    vector<int> ivec2( &arr[1], arr+4);

    //遍历2
    for(int i=0; i<ivec2.size(); i++)
        cout << ivec2[i] << " ";
    cout << endl;

    return 0;
}