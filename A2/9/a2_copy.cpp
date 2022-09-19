#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<forward_list>
using namespace std;

// 容器的拷贝

int main(){
    list<string> authors = {"Milton", "Shakespears", "Austen"};
    vector<const char*> articles = {"a", "an", "the"};

    list<string> list2(authors); //正确：类型匹配
    //deque<string> authList(authors); //错误: 容器类型不匹配
    // error: no matching function for call to ‘
    
    //vector<string> words(articles);  //错误: 容器类型必须匹配
    //error: no matching function for call to

    // 正确，可以将 const char* 元素转换为 string
    forward_list<string> words(articles.begin(), articles.end());

    //Part 2
    for(auto i : articles){
        cout << i << "\t";
    }
    cout << endl;

    //拷贝后
    for(auto i : words){
        cout << i << "\t";
    }
    cout << endl;

   return 0;
}