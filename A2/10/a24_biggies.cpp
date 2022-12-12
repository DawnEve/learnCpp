#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// fn1 字典排序，去重
void elimDups(vector<string> &svec){
    //排序
    sort(svec.begin(), svec.end());
    //保持唯一
    auto iter=unique(svec.begin(), svec.end());
    //删除后面的重复元素
    svec.erase(iter, svec.end());
}

// fn2 根据个数，确实是否用名词复数
string make_plural(int len, string s1, string s2){
    if(len<=1) return s1;
    return s1+s2;
}

// 完整的 biggies，使用多个算法函数
void biggies(vector<string> &words,  vector<string>::size_type sz){
    //1.将words按字典序排序，删除重复的单词
    elimDups(words); 
    //2.按长度排序，长度相同的单词维持字典序，参数3是lambda表达式
    stable_sort(words.begin(), words.end(), 
        [](const string &a, const string &b){ return a.size() < b.size(); });
    //3.获取迭代器，指向第一个满足 size()>=sz 的元素
    auto wc=find_if( words.begin(), words.end(), [sz](const string &s){ return s.size() >= sz; });
    //4.计算满足 size>=sz 的元素的数目
    auto count = words.end() - wc;
    cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << endl;
    //5.打印>=某长度的单词，每个单词后面空格，使用函数 for_each()，对前2个迭代器指定的范围，使用参数3的函数/lambda
    for_each(wc, words.end(), [](const string &s){ cout << s << " ";});
    cout << endl;
}


int main(){
    vector<string> svec2={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    biggies(svec2, 5);
}