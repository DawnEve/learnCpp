#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<string> svec; //默认初始化，svec不含任何元素。
    // 最常见的方式：先定义一个空vector，运行时获取到的元素的值后再逐一添加

    // 列表初始化
    vector<string> vs1={"this", "is", "a", "book"}; 
    vector<string> vs2{"this", "is", "a", "book"};
    //vector<string> vs3("this", "is", "a", "book"); //报错：不能使用圆括号

    // 遍历容器中的元素
    for(int i=0; i<vs1.size(); i++)
        cout << i << " " << vs1[i] << endl;

    return 0;
}