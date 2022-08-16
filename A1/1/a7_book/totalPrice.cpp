#include<iostream>
#include<string>
#include"Book.h"

using namespace std;

int main(){
    Book b1=Book("XX-3-Y-S", 90.80, 5);
    std::cout << ">>>Price of this book is: $";
    std::cout << b1.getPrice() << std::endl;
    return 0;
}