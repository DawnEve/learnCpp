#include<iostream>
using namespace std;

int i=0;

void process_input(istream &is){
    cout << "input an int:" << endl;
    is >> i;
    cout << "i = " << i << endl;
}

void test(){
    // 记住 cin 的当前状态
    cout << "input a letter, to make an err state:" << endl;
    cin >> i;
    getchar();

    auto old_state = cin.rdstate(); //记住 cin 的当前状态
    cout << "1 cin.rdstate=" << cin.rdstate() << endl;
    
    cin.clear();          //使cin有效
    cout << "2 cin.rdstate=" << cin.rdstate() << endl;
    
    process_input(cin);    // 使用 cin
    cout << "3 cin.rdstate=" << cin.rdstate() << endl;
    
    cin.setstate(old_state); //将cin置为原有状态
    cout << "4 cin.rdstate=" << cin.rdstate() << endl;
}

int main(){
    test();
    return 0;
}