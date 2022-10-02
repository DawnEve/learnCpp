#include<iostream>
#include<vector>
#include<list>
using namespace std;

// insert的另一个重载: iter, num, value
void demo1(){
    vector<string> svect={"hi"};
    auto xx = svect.insert(svect.end(), 3, "Tomcat");
    cout << *xx << ", " << &*xx << endl;

    auto be=svect.begin();
    cout << *be << ", " << &*be << endl;
    be++;
    cout << *be << ", " << &*be << endl;
}


// insert 重载: iter, iter1, iter2
void demo2(){
    vector<string> source={"this", "is", "a", "book"};
    vector<string> svect={"dest"};
    //把source的最后2个元素插入到svect的末尾
    auto xx=svect.insert(svect.end(), source.end()-2, source.end()); 
    cout << *xx << ", " << &*xx << endl;
    
    auto be=svect.begin();
    cout << *be << ", " << &*be << endl;
}

// 通过insert的返回值，在一个位置反复插入元素
void demo3(){
    list<string> lst={"hello"};
    auto iter=lst.begin();
    string word;
    cout << "Please input some word, end with Ctrl+D" << endl;
    while(cin >> word)
        iter=lst.insert(iter, word); //等价于 push_front
    
    //打印
    for(auto i: lst)
        cout << i << " ";
    cout << endl;
}

int main(){
    demo1();
    cout << endl;
    demo2();
    cout << endl;
    demo3();

    return 0;
}