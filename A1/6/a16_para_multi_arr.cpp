#include<iostream>
using namespace std;

//传递多维数组，要传递第二维及之后的维度
//void print(int (*arr)[2], int rowSize){
void print(int arr[][2], int rowSize){ //等价形式
    for(int i=0; i<rowSize; ++i){
        for(int j=0; j<2; ++j){
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}


int main(){
    int arr2[3][2]={ {1,2}, {10,20}, {100,200} };
    print(arr2, 3);

    return 0;
}