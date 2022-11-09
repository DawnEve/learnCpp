#include<iostream>
using namespace std;

class Person{
public:
    int i=0;
    virtual void show(){
        cout << "class Person: i=" << i << endl;
    }
};

class Club{
public:
    Person *ptr=NULL;
    // 参数是 对象，则传参时发生了拷贝复制，1)里面获取 对象的指针变了，确实发生了拷贝复制。
    // 为什么 2) 构造作用域结束，指针指向的 拷贝复制的对象 还不销毁？用gcc是这样，用 msvc 编译报错
    Club(Person person){
        //person.i=100;
        (&person)->i=100;

        cout << "in Fn: &person=" << &person << ", i=" << person.i << endl;
        ptr=&person;
        cout << ptr << endl;
    }

    void show(){
        if(ptr != NULL){
            cout << ptr << ": " << ptr->i << endl;
            ptr->show();
        }
    }
};

int main(){
    Person p1;
    p1.show();
    cout << "&p1 = " << &p1 << endl;

    printf("\n");
    Club club(p1);
    club.show();
    cout << "out Fn: " << p1.i << endl;
    cout << "End:  club.ptr->i=" << club.ptr->i << 
        ", addr: "<< club.ptr << endl;

    return 0;
}