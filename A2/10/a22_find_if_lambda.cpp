#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<string> s2={"this", "is", "a", "black", "cat"};
    string::size_type sz=5;
    // 获取一个迭代器，指向第一个满足 size()>=sz 的元素
    auto rs=find_if(s2.begin(), s2.end(), 
        [sz](const string &s){
            return s.size()>=sz;
        }
    );
    cout << *rs << endl;
    cout << "length:" << s2.end()-rs << endl;
    return 0;
}