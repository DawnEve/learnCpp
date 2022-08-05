#include<iostream>
using namespace std;

// 两层嵌套for处理多维数组
int main(){
    constexpr size_t rowCnt=3, colCnt=4;
    int ia[rowCnt][colCnt]; //12个未初始化的元素

    // 对于每一行
    for(size_t i=0; i!=rowCnt; ++i){
        //对于行内的每一列
        for(size_t j=0; j!=colCnt; ++j){
            //将元素的位置索引作为它的值
            ia[i][j] = i*colCnt + j;
            cout << ia[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}