#include<iostream>
using namespace std;

//test: 类类型的数组不赋值是啥
class Stu{
public:
    int age;
    Stu(){
        cout << "Stu()" << endl;
    }
    Stu(int x):age(x){}
};

class ClassRoom{
private:
    Stu stu[5]; //走默认构造函数，如果没有默认构造函数，则报错。
public:
    void show(){
        for(auto s: stu){
            cout << s.age << endl; //都是0
        }
    }
};


int main(){
    ClassRoom cr1; //走默认构造函数，其中的Stu [5]也走默认构造函数
    cr1.show();

    return 0;
}