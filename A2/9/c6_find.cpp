#include<iostream>
using namespace std;

void demo1(){
    string name("this is a cpp book");
    auto pos1= name.find("is");
    cout << pos1 << endl; //2

    //搜不到时
    auto pos2= name.find("python");
    cout << pos2 << endl; //18446744073709551615

    //怎么判断未找到？
    if( pos2== string::npos ){
        cout << "not found!" << endl;
    }
}

//找第一个在 or 不在参数中的字符
void demo2(){
    string numbers("0123456789"), addr("6375b1");
    auto pos=addr.find_first_of(numbers);
    cout << pos << endl;  //0  addr中第0个字符‘6’首次出现在 numbers中

    auto pos2=addr.find_first_not_of(numbers); //addr 中第4个字符‘b’不在 numbers中
    cout << pos2 << endl;  //4
}

// find 的其他参数形式
void demo3(){
    string msg="this is a book", s2="is";
    auto pos=msg.find("is"); //第一次出现的位置 2
    cout << pos << endl; 

    pos=msg.rfind("is"); //最后一次出现的位置 5
    cout << pos << endl; 

    pos=msg.find(s2, 3); //5  从msg的第三个字符开始查找字符 is
    cout << pos << endl; 
}


// s.find(s2)是给出s中s2首次出现的下标，怎么给出所有s2的下标？
void demo4(){
    string::size_type pos=0;
    string s1="this is a book, which is about C++", s2="is";
    while( (pos = s1.find(s2, pos)) != string::npos ){
        cout << "found s2 at index:" << pos 
            << " element is: " << s1.substr(pos) << endl;
        pos++;
    }
}

int main(){
    //demo1();
    //demo2();
    //demo3();
    demo4();
}