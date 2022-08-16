#include<iostream>
#include<vector>
using namespace std;

/******* 声明 ******/

class Screen{
public:
    //类型别名，也受访问控制： public or private
    //typedef std::string::size_type pos; //类别名
    using pos = std::string::size_type; //等价声明，同上

    // 构造函数
    Screen() = default; //有其他构造函数，就必须定义默认构造函数
    Screen(pos h, pos w, char c): height(h), width(w), contents( h * w, c){}

    // 成员函数
    char get() const { //读取光标处的字符，隐式内联
        return contents[cursor]; 
    }
    inline char get(pos h, pos w) const ; //显式内联
    Screen &move(pos r, pos c); //能在之后设置为内联
    
    //设置字符
    Screen &set(char);
    Screen &set(pos, pos, char);
    //Screen &display(ostream&);
    //根据对象是否const重载display函数
    Screen &display(std::ostream &os){
        cout << "version: non-const" << endl;
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const {
        cout << "version: const" << endl;
        do_display(os);
        return *this;
    }

    void show(){
        cout << contents << endl;
    }

private:
    pos cursor = 0;
    pos height =0, width = 0;
    std::string contents;
    //负责打印Screen 的内容
    void do_display(std::ostream &os) const{
        os << contents << std::endl;
    }
};

class Window_mgr{
private:
    // 这个 Window_mgr 追踪的 Screen
    // 默认情况下，一个 Window_mgr 包含一个标准尺寸的空白 Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};



/******* 定义 ******/
inline                                 //在函数的定义处指定 inline
Screen& Screen::move(pos r, pos c){
    pos row = r * width;
    cursor = row + c; //位置 = 行*宽度 + 列
    return *this; //以左值的形式返回对象
}

char Screen::get(pos r, pos c) const {  //在类内部声明为 inline
    pos row = r * width; //计算 位置
    return contents[row + c]; //返回给定列的字符
}

inline Screen &Screen::set(char c){
    contents[cursor]=c; // 设置当前光标所在位置的新值
    return *this; //将this对象作为左值返回
}
inline Screen &Screen::set(pos r, pos c, char ch){
    contents[r*width + c]=ch; // 设置当前光标所在位置的新值
    return *this; //将this对象作为左值返回
}
/*
inline Screen &Screen::display(ostream &os){
    os << this->contents << endl;
    return *this; //将this对象作为左值返回
}
*/

int main(){
    Screen screen(4, 5, 'z');
    char ch=screen.get(); //调用 Screen::get();
    cout << ch << endl;

    ch = screen.get(0,2); //调用 Sceen::get(pos, pos)
    cout << ch << endl;

    screen.display(cout).move(3,0).set('#').display(cout);
    //screen.show();

    // 常量版本:
    const Screen blank(5,3, ' ');
    blank.display(cout).display(cout); //调用常量版本



    //string test(5, 'c');
    //cout << test << endl;

    return 0;
}