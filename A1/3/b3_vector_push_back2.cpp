#include<iostream>
#include<vector>
using namespace std;

// 读入不定个数的字符串

int main(){
    // v.push_back(item) 在v的末尾添加元素item
    vector<string> line;
    string word;

    cout << "Please input some words:" << endl;
    while(cin >> word)
        line.push_back(word); 

    //输出
    for(int i=0; i<line.size(); i++)
        cout << i << " " << line[i] << endl;
    
    return 0;
}