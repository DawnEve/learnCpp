#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main(){
    list<string> lst={"this", "is", "a value"};
    string val="a value2";
    auto result=find(lst.cbegin(), lst.cend(), val);
    cout << "The value '" << val << 
        (result==lst.cend() ? "' is NOT in list": "' is in list") << endl;
    return 0;
}