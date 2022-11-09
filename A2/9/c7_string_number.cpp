#include<iostream>
using namespace std;

//数字的字符形式 与数字的互转

//打印二进制
void show_byte(unsigned char *ptr){
    for(int i=7; i>=0; i--){
        printf("%c", ((*ptr) & (1<<i))?'1':'0' );
    }
    printf(" ");
}

void show_bytes(unsigned char *ptr, int num){
    for(int i=num-1; i>=0; i--){
        show_byte( ptr + i );
    }
    printf("\n");
}

void demo1(){
    short a1=15; //数字 15
    show_bytes( (unsigned char *)&a1, sizeof(a1));

    // 字符串形式的 15
    string a2="15";
    const char *pa2=a2.c_str();
    printf("%p, %s, sizeof=%ld, size=%ld\n", pa2, pa2, sizeof(pa2), a2.size());
    //show_bytes( (unsigned char *)pa2, a2.size());
    //show_bytes( (unsigned char *)pa2, sizeof(pa2) ); //不应该倒着看，因为这不是一个变量内。字符一直是正序的
    show_byte( (unsigned char *)pa2 );
    show_byte( ((unsigned char *)pa2)+1 );
    printf("\nthe 2 chars are: %s\n", (unsigned char *)pa2);

    printf("\n\n");
    //单个字符
    unsigned char b1='1', b2='5';
    show_byte( &b1); printf("\n");
    show_byte( &b2); printf("\n");
}


//实现数值数据与 标准库string之间的转换
void demo2(){
    int i=15;
    string s=to_string(i); //整数 to string

    double d= stod(s); //字符串s转换为浮点数
    cout << s << endl;
    cout << d << endl;
}

//字符串转为数字，第一个字符必须是数字可能出现的字符
void demo3(){
    string s1="3.1415926535897932"; //这样可以
    double d=stod(s1);
    printf("%0.9lf\n", d);

    string s2="pi = 3.1415926"; //直接转数字，运行时报错:  what():  stod  Aborted (core dumped)
    double d2=stod(s2.substr(s2.find_first_of("+-.0123456789")));
    cout << d2 << endl;

}


int main(){
    //demo1();
    //demo2();
    demo3();
}


