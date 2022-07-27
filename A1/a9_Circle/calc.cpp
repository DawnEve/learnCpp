#include<iostream>
#include "Circle.h"

using namespace std;

int main(){
    Circle c=Circle(4);
    cout << "Area = " << c.Area() << endl;
    return 0;
}

/*
$ g++ -c A1/a9_Circle/Circle.cpp -o Circle.o
$ g++ A1/a9_Circle/calc.cpp Circle.o
$ ./a.out 
Area = 50.24
*/