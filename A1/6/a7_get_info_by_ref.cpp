#include<iostream>
using namespace std;

//通过引用形参获取额外信息

string::size_type find_char(const string &s, char ch, 
                string::size_type &cnt){
    auto ret= s.size(); //字符长度
    cnt=0; //字符出现的总次数
    for(decltype(ret) i=0; i<s.size(); ++i){
        if(s[i]==ch){
            ++cnt; //出现次数计数器
            if(ret == s.size()){ //这个初始值是比最大下标还大1的，没改变就表示没找到。
                ret =i; //第一次出现的位置
            }
        }
    }
    return ret;
}

int main(){
    string s2="This is a book.";    
    cout << "Input a char:" << endl;
    char char2;
    cin >> char2;

    //开始统计
    string::size_type totalCnt=0;
    string::size_type start=find_char(s2, char2, totalCnt);
    // 输出: 字符出现总次数，首次出现的下标
    cout << endl;
    cout << "the char:" << char2 << endl;
    cout << "in string:" << s2 << endl;
    cout << "Total count:" << totalCnt << ", first index:" << start << endl;

    return 0;
}