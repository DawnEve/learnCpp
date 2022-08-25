#include<iostream>
using namespace std;

//关联输入流和输出流：保证在读之前，输出所有用户提示

int main(){
    int i;
    cin.tie(&cout); //仅仅使用从来展示：标准库将cin和cout关联在一起

    //old_tie 指向当前关联到cin的流（如果有的话）
    ostream *pold_tie = cin.tie(nullptr); //cin 不再与其他流关联

    //test
    //cerr << "some error:";
    cout << "input an int:";
    cin >> i;

    //将cin与cerr关联：这不是一个好主意，因为cin应该与cout关联
    cin.tie(&cerr); //读取cin会刷新cerr而不是cout
    cin.tie(pold_tie);  //重建 cin 和 cout 间的正常访问

    return 0;
}