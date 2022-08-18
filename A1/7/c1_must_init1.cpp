#include<iostream>
using namespace std;

// 必须初始化的情形：是引用或const成员
class ConstRef{
public:
    ConstRef(int ii);
private:
    int i;
    const int ci;
    int &ri;
};

/*
ConstRef::ConstRef(int ii){
    i=ii; //正确
    ci=ii; //错误：不能给const赋值
    //error: assignment of read-only member ‘ConstRef::ci’

    ri=i;  //错误：ri没被初始化
    //note: ‘int& ConstRef::ri’ should be initialized
}
*/
//正确：显式的初始化引用和const成员
ConstRef::ConstRef(int ii): i(ii), ci(ii), ri(i){}

int main(){
    // ci 和ri 必须初始化。否则将引发编译错误
    ConstRef cr(10);

    return 0;
}
