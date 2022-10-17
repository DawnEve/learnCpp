#include<iostream>
using namespace std;

int main(){
    string s="hello";
    cout << "1 " << s << endl;
    
    s.insert(s.size(), 5, '!'); //在s的末尾添加5个感叹号
    cout << "2 " << s << endl;

    s.erase(s.size()-5, 5);  //从s删除最后5个字符
    cout << "3 " << s << endl;

    return 0;
}