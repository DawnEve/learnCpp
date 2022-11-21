#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> ivec={1,2,2,2,3,3,4};
    for(int i=1; i<6; i++){
        auto rs=count(ivec.cbegin(), ivec.cend(), i);
        cout << i << ": " << rs << endl;
    }

    return 0;
}