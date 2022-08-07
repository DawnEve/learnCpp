#include<iostream>
#include<vector>
using namespace std;

//返回列表初始化值的函数
vector<string> process(){
    string expected = "hello";
    string actual;
    cout << "Please input hello, otherwise may produce an err msg:" << endl;
    cin >> actual;
    //开始判断
    if( expected.empty())
        return {}; //返回一个空vector 对象
    else if(expected == actual)
        return {"functionX", "okey"}; //返回列表初始化vector
    else 
        return {"functionX", expected, actual};
}

int main(){
    vector<string> msg=process();

    for(auto i: msg)
        cout << i << " ";
    cout << endl;

    return 0;
}