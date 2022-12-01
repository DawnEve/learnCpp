#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void elimDups(vector<string> &svec){
    //排序
    sort(svec.begin(), svec.end());
    //保持唯一
    auto iter=unique(svec.begin(), svec.end());
    //删除后面的重复元素
    svec.erase(iter, svec.end());
}

// 按单词的长度排序
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

void bigger(vector<string> &words, vector<string>::size_type sz){
    //字典排序，去重
    elimDups(words); 
    //按长度排序，等长度的按字典排序
    stable_sort(words.begin(), words.end(), isShorter);
    //打印大于某个长度的单词
    for(auto ele: words){
        if(ele.size() > sz){
            cout << ele<< " ";
        }
    }
    cout << endl;
}

vector<string> svec2={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

void demo1(){
    bigger(svec2, 4);
}


// 定义一元谓词，作为 find_if() 的参数3
bool biggerThan4(string s2){
    return s2.size() >4;
}

void demo2(){
    for(auto ele: svec2)
        cout << ele << " ";
    cout << endl;
    // 获取长度大于n的单词
    // find_if 的3个参数，前2个是一对迭代器，参数3是一个一元谓词。
    //      返回迭代器，指向第一个非0值(就是找到符合要求的元素了)；如果都是0，则指向尾后位置
    auto iter_end=find_if(svec2.begin(), svec2.end(), biggerThan4);
    cout << *iter_end << endl;
    // 打印从头到这个迭代器之前的元素
    for(auto iter=svec2.begin(); iter!=iter_end; iter++)
        cout << *iter <<" ";
    cout << endl;
}

int main(){
    demo1();
    demo2();
    return 0;
}
