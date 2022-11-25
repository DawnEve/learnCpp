#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<string> s1={"this", "is", "a", "book"}, s2={"this", "is", "a", "book2"};
    //s2=s1;
    bool rs=equal(s1.cbegin(), s1.cend(), s2.cbegin());
    cout << rs << endl;
    return 0;
}