#include<iostream>
using namespace std;

// 构建错误信息，使用编译器定义的字符串
bool checkLength(string word, int threshold){
    if(word.size() < threshold){
        cerr << "Error: " << __FILE__ << ": in function " << __func__ 
             << " at line " << __LINE__ << endl //竟然可以换行且继续输出
             << "     Compiled on " << __DATE__ << " at " << __TIME__ << endl 
             << "     Word read was \"" << word
             << "\": Length too short" << endl;
        return false;
    }
    return true;
}

int main(){
    string s2="hi";
    bool rs=checkLength(s2, 5);
    cout << (rs? "ok":"not ok") << endl;

    return 0;
}