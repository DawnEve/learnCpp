#include<iostream>
using namespace std;

struct OS{
    char OS_id;
    OS(char x):OS_id(x){}
};

int main(){
    OS data('\x1e'), *dataPtr=&data;
    printf("OS_id=%c, %d\n", dataPtr->OS_id, dataPtr->OS_id);

    // 16 进制数字的两种表示方法, P37-c++Primer
    printf("1>> %c, %d | %ld\n", 0x1e, 0x1e, sizeof(0x1e));
    printf("2>> %c, %d | %ld\n", '\x1e', '\x1e', sizeof('\x1e'));

    string osVersion{};

    // 这里 switch case 使用了16进制数字？
    switch(dataPtr->OS_id){
        case '\x1e':
            osVersion="Windowns 10";
            printf("1 number is %d\n", 0x1e);
            break;
        case '\x1a':
            osVersion="Windowns 8";
            printf("2 number is %d\n", 0x1a);
            break;
        case '\x17':
            osVersion="Windowns 7 -Xp - Vista";
            printf("3 number is %d\n", 0x17);
            break;
        default:
            osVersion="Unkown os version";        
            printf("4 number is NA\n");
    }

    return 0;
}