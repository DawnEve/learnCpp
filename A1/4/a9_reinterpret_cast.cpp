#include<iostream>
using namespace std;

// reinterpret_cast 是很危险的
int main(){
    int i=65, *ip=&i;
    char *pc = reinterpret_cast<char*>(ip);

    cout << "1 " << *pc << endl;
    string str(pc);
    cout << "2 " << str << endl;

    char *pc2 = (char*) ip; //ip是指向的是整数的指针
    printf("3 %c\n", *pc2);
    cout << "4 " << *pc2 << endl;

    return 0;
}