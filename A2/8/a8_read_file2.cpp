#include<iostream>
#include<fstream>
using namespace std;
// 要引入 fstream 头文件

// read file: iostream
class Book{
public:
    string ISBN;
    int count;
};

istream &read(istream &is, Book &book){
    is >> book.ISBN >> book.count;
    return is;
}

void print(const Book &book){
    cout <<"class Book: " << book.ISBN << " " << book.count << endl;
}

int main(int argc, char *argv[]){
    Book b1, b2;
    //1.read from cin
    cout << "Pls input Book info: isbn count:" << endl;
    read(cin, b1);
    print(b1);

    //2.read from file
    ifstream input(argv[1]);
    //read(input, b2);
    //print(b2);
    while( read(input, b2) ){
        print(b2);
    }

    return 0;
}

/*
$ cat a8_file2.txt 
S1 40
S2 10

$ g++ a8_read_file2.cpp 
$ ./a.out a8_file2.txt 
Pls input Book info: isbn count:
S102 100
class Book: S102 100
class Book: S1 40
class Book: S2 10
*/