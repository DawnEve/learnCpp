#include<iostream>
using namespace std;

class Book{
public:
    int i;
    Book(int x=0): i(x){
        cout << "Book()" << endl;
    }
    ~Book(){
        cout << "~Book()" << endl;
    }
};

int main(){
    Book *book = new Book(200);
    cout << book->i << endl;
    delete book;
    // in while
    int x=3;
    //for(int i=0; i<x; i++){
    int i=x; while(i--){
        Book book(i);
        cout << book.i << endl;
    }

    return 0;
}