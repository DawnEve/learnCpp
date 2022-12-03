#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> ivec={1,3,5,7,9};
    // 参数3是lambda表达式
    for_each(ivec.begin(), ivec.end(), 
        [](const int &s){  cout << s << " "; }
    );
    cout << endl;
    return 0;
}