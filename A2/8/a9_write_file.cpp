#include<iostream>
#include<fstream>
using namespace std;

//写入文件，先重普通输出，在写入文件

// write file: iostream
class Book{
public:
    string ISBN;
    int count;
};

//读数据
istream &read(istream &is, Book &book){
    is >> book.ISBN >> book.count;
    return is;
}

//写数据
ostream &print(ostream &os, const Book &book){
    os <<"class Book: " << book.ISBN << " " << book.count << endl;
    return os;
}

int main(int argc, char *argv[]){
    Book b1, b2;
    //1.一直从键盘读数据
    cout << "Pls input Book info: isbn count:" << endl;
    read(cin, b1);
    print(cout, b1);
    //写到文件
    ofstream output(argv[1]);
    print(output, b1);
    cout << "save to file now:" << argv[1] << endl;

    return 0;
}

/*
$ g++ a9_write_file.cpp

$ ./a.out a9.txt
Pls input Book info: isbn count:
S100 200
class Book: S100 200

$ cat a9.txt 
class Book: S100 200
*/