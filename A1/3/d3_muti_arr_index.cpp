#include<iostream>
using namespace std;

// 多维数组的下标引用
int main(){
    // define
    int arr[]={0,1,2,3,4};
    int ia[3][4]={0};
    ia[2][3] = arr[3]; //arr[3] 是一个元素，赋值给 ia 最后一行、最后一列的元素

    int (&row)[4] = ia[2]; //把row绑定到 ia 的第3个 四元素上。
    // 定义从内向外看： row 是一个引用，指向一个4元素数组，元素是int。

    // output
    for(int i=0; i<3; i++){
        for(int j=0; j<4; j++){
            cout << ia[i][j] << "\t";
        }
        cout << endl;
    }
    // output: row 就是 ia[2] 的别名
    for(int i=0; i<4; i++)
        cout << row[i] << " - " << ia[2][i]<< endl;

    return 0;
}