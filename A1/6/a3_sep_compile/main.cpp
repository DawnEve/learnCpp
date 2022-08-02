#include<iostream>
#include "fact.h"
using namespace std;

int main(){
    int value=0;
    cout << "input an int:" << endl;
    cin >> value;
    cout << value << "!=" << fact(value) << endl;
}