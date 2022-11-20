#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> ivec={1,2,5,9,10,15};
    int val=10;
    auto result=find(ivec.begin(), ivec.end(), val);
    cout << "The value " << val << 
        (result==ivec.end() ? " is NOT in vector": " is in vector") << endl;
    return 0;
}