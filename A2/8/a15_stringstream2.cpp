#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

// stringstream 示例
// 注意: 要加头文件 #include<sstream>

struct PersonInfo{
    string name;
    vector<string> phones;

    void show(){
        cout << "> " << name << ":";
        for(auto i : phones){
            cout << i << " / ";
        }
        cout << endl;
    }
};

//验证字符串
bool valid(const string &s){
    if(s.size() < 3)
        return false;
    string s2("200");
    if(s < s2)
       return false;
    return true;
}
//格式化字符串
string format(string s){
    s = "010-" + s;
    return(s);
}

int main(){
    //打开文件
    ifstream fin("a15.txt");

    // 从文本文件读取
    string line, word;  //分别保存输入的一行和单词（电话号码）
    vector<PersonInfo> people;  //保存来自输入的所有记录
    // 逐行读入数据，直到 cin 遇到文件末尾(或其他错误)
    while(getline(fin, line)){
        PersonInfo info;  //创建一个结构体对象
        istringstream record(line); //将记录绑定到刚读入的行
        record >> info.name; //记录名字
        while( record >> word){ //读取电话号码: 从字符流读取
            info.phones.push_back( word ); // 将电话追加到 号码向量
        }
        people.push_back(info); //将一行记录追加到 people 末尾
    }

    // 关闭文件
    fin.close();

    // 输出
    //打开输出文件
    ofstream os("a15o.txt");
    for(const auto &entry: people){ //遍历people中的每一项
        ostringstream formatted, badNums; //每个循环步骤创建的对象
        for(const auto &nums: entry.phones){ //对每个数
            if(!valid(nums)){
                badNums << " " << nums; //将数的字符串形式存入 badNums
            }else{
                // 将格式化的字符串"写入"formatted
                formatted << " " << format(nums);
            }
        }
        // 一条有一个错误的，这一条就不输出了
        if(badNums.str().empty()) { //没有错误的数字
            os << entry.name << " " 
               << formatted.str() << endl; //打印名字和格式化的数
        }else{
            cerr << "input error: " << entry.name 
                 << " invalid number(s) " << badNums.str() << endl;
        }
    }
    //关闭文件
    os.close();

    return 0;
}
