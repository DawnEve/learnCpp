#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

int main(){
    vector<string> s1={"this", "is"};
    list<const char*> s2={"this", "is"}, s3={"this", "is3"}, s4={"this", "is", "a"};
    cout << equal(s1.cbegin(), s1.cend(), s2.cbegin()) << endl; //1
    cout << equal(s1.cbegin(), s1.cend(), s3.cbegin()) << endl; //0
    cout << equal(s1.cbegin(), s1.cend(), s4.cbegin()) << endl; //1
    return 0;
}