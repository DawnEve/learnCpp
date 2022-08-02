#include<iostream>
using namespace std;

// 形参尽可能使用常量引用

string::size_type find_char(const string &s, char ch, string::size_type &cnt){ //version1: 提倡
//string::size_type find_char(string &s, char ch, string::size_type &cnt){ //version2
    // 返回符号ch首次出现的位置，通过引用获取符号ch出现的总次数cnt
    string::size_type pos=s.size();
    cnt=0;
    for(string::size_type i=0; i<s.size(); i++){
        if(s[i] == ch){
            ++cnt; //计数器
            if(pos==s.size()){
                pos=i;
            }
        }
    }
    return pos;
}


// 如果s2的结尾有且仅有一个句号，则s2是一个句子
bool is_sentence(const string &s2){
    string::size_type count=0;
    return find_char(s2, '.', count) == s2.size()-1 && count ==1;
}


int main(){
    string s2="hello, world.";
    char cha='o';
    string::size_type count=0;
    string::size_type index=find_char(s2, cha, count);
    //string::size_type index=find_char("good", cha, count); //可以传入字面量 only for version1.
    //
    cout << "str: " << s2 << endl;
    cout << "char:" << cha << endl;
    cout << "first index:" << index << ", count:" << count << endl;

    bool isSts=is_sentence(s2); //只支持const的 version1，否则报错
    string msg = (isSts? "is":"is not") + string(" a sentence.");
    cout << s2 << msg << endl;

    return 0;
}