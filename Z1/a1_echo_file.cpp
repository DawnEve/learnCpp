#include<iostream>
using namespace std;

// 模仿linux命令 cat

/*
$ g++ -o cat2 a1_echo_file.cpp
$ ./cat2 > 2.txt
this is a book ctrl+D

$ ./cat2 < 2.txt
$ ./cat2 < a1_echo_file.cpp
*/

int main(){
    char ch;
    while( (ch=getchar() )!=EOF  ){
            putchar(ch);
    }
    //putchar('\n');
    return 0;
}