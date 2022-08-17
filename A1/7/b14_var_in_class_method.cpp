#include<iostream>
using namespace std;

// 函数中变量的查找顺序
/*
dummy_fcn 的 height 是哪个？
1.函数内，使用前：是形式参数
2. 如果想使用成员变量，则可以使用 this->height 或 Screen::height
*/

int height; //定义一个名字，稍后将在 Screen 中使用
class Screen{
public:
    typedef std::string::size_type pos;
    void dummy_fcn(pos height){
        //cursor = width * height;  //哪个 height？是传入的参数

        //不好的写法，成员函数中的名字不应该隐藏同名的类成员
        //cursor = width * this->height; //height是类的私有成员
        cursor = width * Screen::height; //height是类的私有成员
    }
    void show(){ cout << cursor << endl;}
private:
    pos cursor=0;
    pos height=1, width=1;
};

int main(){
    Screen scr1;
    scr1.dummy_fcn(50);
    scr1.show();
    return 0;
}