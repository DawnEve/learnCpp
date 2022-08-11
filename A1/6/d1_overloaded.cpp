#include<iostream>
using namespace std;

struct Record{
    char acount;
    int phone;
    string name;
};

Record arr[]={
    {'a', 123, "Tom"},
    {'b', 456, "Lily"},
    {'c', 789, "Lilei"}
};
Record empty={'\0', 0, ""};

//重载函数的声明
Record lookup(const char&); //根据acount查找
Record lookup(const int&); //根据phone查找
Record lookup(const string&); //根据name查找

void print(Record r){
    cout << "struct Record: "<< r.acount << ", " << r.phone << ", " << r.name << endl;
}


int main(){
    char acct='b';
    int phone=123;
    string name="Lilei";

    Record r1=lookup(acct);
    Record r2=lookup(phone);
    Record r3=lookup(name);

    print(r1);
    print(r2);
    print(r3);
    return 0;
}


Record lookup(const char& c){
    cout << ">lookup by account: char " << c << endl;
    for(int i=0; i<3; i++){
        if(arr[i].acount == c)
            return arr[i];
    }
    return empty;
}

Record lookup(const int& n){
    cout << ">lookup by phone: int " << n << endl;
    for(int i=0; i<3; i++){
        if(arr[i].phone == n)
            return arr[i];
    }
    return empty;
}

Record lookup(const string& s){
    cout << ">lookup by name: string " << s << endl;
    for(int i=0; i<3; i++){
        if(arr[i].name == s)
            return arr[i];
    }
    return empty;
}
