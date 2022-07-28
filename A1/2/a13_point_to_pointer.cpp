#include<iostream>
using namespace std;

int main(){
    int ival=1024;
    int *pi=&ival; //pi指向一个int型的数
    int **ppi=&pi; //ppi指向一个 int型的指针
    
    // 使用 *addr 获取该指针指向的地址的值
    cout << "&ppi=" << &ppi << ", \tppi=" << ppi 
         << ", \t*ppi=" << *ppi << ", \t**ppi=" << **ppi << endl;
    cout << "&pi=" << &pi << ", \tpi=" << pi << ", \t*pi=" << *pi << endl;
    cout << "ival=" << ival << ", \taddr=" << &ival << endl;

    // 使用 &获取地址
    cout << "\nppi=" << ppi << " ==> &pi=" << &pi << ", pi=" << pi << " ==> &ival=" << &ival << endl;
    return 0;
}