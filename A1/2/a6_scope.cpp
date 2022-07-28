#include<iostream>
using namespace std;

int book_number=1;

int main(){

    cout << "book_number in global = " << book_number << endl;

    int book_number=100;
    cout << "book_number (in main) = " << book_number << endl;
    cout << "::book_number (in global) = " << ::book_number << endl;

    return 0;
}