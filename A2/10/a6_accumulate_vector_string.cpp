#include<iostream>
#include<numeric>
#include<vector>

using namespace std;

int main(){
    vector<string> svec={"this", "is", "a", "book"};
    //输出
    for(auto i: svec)
        cout << i << endl;
    // 连起来
    string sum2=accumulate(svec.begin(), svec.end(), string(""));
    
    //string sum2=accumulate(svec.begin(), svec.end(), ""); //字符串字面量当第三个参数报错: const char* 没有定义+运算符
    //error: cannot convert ‘std::__cxx11::basic_string<char>’ to ‘const char*’ in assignment
    
    cout << "sum2=" << sum2 << endl;
    return 0;
}