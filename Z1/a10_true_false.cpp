#include<iostream>
using namespace std;

// true 和 false 是不是新的数据类型？
int main(){
    bool x=true, y=false;
    printf("sizeof x:%ld, y:%ld\n", sizeof(x), sizeof(y)); //占了一个字节
    
    // 打印出其16进制
    printf("value x:0x%x, y:0x%x\n", x, y);

    return 0;
}