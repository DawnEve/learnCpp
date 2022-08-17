#include<iostream>
#include<vector>
using namespace std;

//声明 Window_mgr::clear函数 为 Screen 类的友元，需要注意程序结构
//1. 声明Screen类。定义 Window_mgr 类，声明clear函数(不能定义，因为还没有Screen类)
class Screen;

class Window_mgr{
public:    
    void clear(int x);
    Window_mgr& push(Screen);

    Screen &get(int i){
        return screens[i];
    }
private:
    vector<Screen> screens;
};

//2. 定义Screen类，包括对clear的友元声明
class Screen{
    friend void Window_mgr::clear(int);
public:
    Screen(char ch){
        contents = string(10, ch);
    }
    void print(string s=""){ cout << s << contents << endl;}
private:
    string contents; //(10, '*');
};

//3. 最后定义Window_mgr::clear函数
void Window_mgr::clear(int x){
    Screen &s = screens[x];
    s.contents="";
}

Window_mgr& Window_mgr::push(Screen s1){
    screens.push_back(s1);
    return *this;
}

int main(){
    Window_mgr win_mgr;
    Screen scr1('#'), scr2('+');
    win_mgr.push(scr1).push(scr2);
    //查看
    win_mgr.get(0).print("1:");
    win_mgr.get(1).print("2:");

    //获取第0个
    Screen &cscr1 = win_mgr.get(0);
    cscr1.print("b 1:");
    //清空 下标是0的内容
    win_mgr.clear(0);
    cscr1.print("a 1:");

    //再次查看
    win_mgr.get(0).print("1:");
    win_mgr.get(1).print("2:");

    return 0;
}