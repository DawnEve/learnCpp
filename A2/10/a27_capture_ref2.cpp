#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 捕获引用: 接受一个 ostream 的引用，用来输出数据，并指定分隔符
void print(vector<string> &words, 
    vector<string>::size_type sz,
    ostream &os=cout,  char c=' '){
    for_each(words.begin(), words.end(), 
        [&os, c](const string &s){ os<< s << c;});
    os << endl;
}

int main(){
    vector<string> words={"this", "is", "a", "book"};
    print(words, words.size(), cout, '-');
    return 0;
}