#include<iostream>
#include<vector>
using namespace std;

void test1(){
    vector<string> vec1;
    string word;
    int i=0;
    cout << "input 2 word:" << endl;
    while(cin >> word){
        vec1.push_back(word);
        if(++i >1)
            break;
    }

    for(auto i: vec1){
        cout << i << ", ";
    }
    cout << endl;
}


// 对字符串
void pluralize(size_t cnt, string &word){
    if(cnt>1)
        word.push_back('s'); //等价于 word += 's';
}

void test2(){
    string s1="boat";
    pluralize(3, s1);
    cout << s1 << endl;
}

int main(){
    test1();
    test2();
}