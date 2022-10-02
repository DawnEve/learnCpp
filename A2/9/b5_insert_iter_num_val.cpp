#include<iostream>
#include<vector>
#include<list>
using namespace std;

void print(vector<string> &v);

// insert的另一个重载: iter, num, value
void demo1(){
    vector<string> svect;
    svect.insert(svect.end(), 3, "Tomcat");

    for(auto i: svect)
        cout << i << " ";
    cout << endl;
}

// insert 重载: iter, iter1, iter2
void demo2(){
    vector<string> source={"this", "is", "a", "book"};
    vector<string> svect={"dest"};
    //把source的最后2个元素插入到svect的末尾
    svect.insert(svect.end(), source.end()-2, source.end()); 
    print(svect);
}

void demo2_bug(){
    vector<string> svect={"dest", "nobug"};
    //把source的最后2个元素插入到svect的末尾
    print(svect);
    svect.insert(svect.end(), svect.begin()-2, svect.end()); // 啥也没做
    print(svect);
}

void demo2_bug2(){
    list<string> slist={"dest", "A"};
    // $ g++ -std=c++11 b5_insert_iter_num_val.cpp
    // $ ./a.out
    // dest A dest A  #没有报错.... 
    slist.insert(slist.end(), slist.begin(), slist.end()); //正常插入
    for(auto i: slist)
        cout << i << " ";
    cout << endl;
}

// insert 重载：iter, il(初始化列表)
void demo3(){
    vector<string> svect={"dest"};
    svect.insert(svect.end(), {"hi", "Tomcat"});
    print(svect);
}




int main(){
    //demo1();
    //demo2();
    //demo2_bug();
    demo2_bug2();
    //demo3();
    return 0;
}



void print(vector<string> &v){
    for(auto i: v)
        cout << i << " ";
    cout << endl;
}