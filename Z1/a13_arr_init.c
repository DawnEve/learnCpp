#include<stdio.h>

int main(){
    int x=2, arr[5]={x*5}; //没有报错: 初始化列表可以有变量
    for(int i=0; i<5; i++)
        printf("%d\n", arr[i]);
    printf("\n");
}
