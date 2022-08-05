#include<iostream>
using namespace std;

// 范围for遍历二维数组
int main(){
    int ia[2][3];

    //遍历初始化
    size_t cnt=0;
    for(auto &row : ia){ // 对于外层的每个元素(都是数组)
        for(auto &col: row){ //对于内层的每个元素(都是int)
            col = cnt;
            ++cnt;
        }
    }

    //遍历输出
    for(auto &row : ia){ //外循环一定要声明成引用类型，因为内循环要用。
        for(auto col: row){
            cout << col << "\t";
        }
        cout << endl;
    }

    return 0;
}