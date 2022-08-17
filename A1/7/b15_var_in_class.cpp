#include<iostream>
using namespace std;

// 定义在类外的成员函数，名字查找顺序：考虑类前作用域、考虑方法定义前的作用域
int height;  //定义了一个名字，稍后在Screen 中使用
class Screen{
public:
    typedef std::string::size_type pos;
    void setHeight(pos);
    pos height = 0; //隐藏了外层作用域中的同名 height
};

Screen::pos verify(Screen::pos);

//全局函数 verify 的声明在类的定义前是不可见的。然而，名字查找的第三步，包括了成员函数定义前的全局作用域。
// 该例中，verify 声明出现在定义 setHeight 前，可以正常访问
void Screen::setHeight(pos var){
    // var: 参数
    // height: 类的成员
    // verify: 全局函数
    height = verify(var);
}

int main(){
    Screen scr1;
    scr1.setHeight(25);
    cout << scr1.height << endl;

    return 0;    
}

Screen::pos verify(Screen::pos ht){
    if(ht>1e4){
        return 1e4;
    }
    return ht;
}