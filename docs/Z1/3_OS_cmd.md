# 系统命令



## OS 系统交互


运行系统命令 `ls`。
```
#include<iostream>
using namespace std;

int main(){
    cout << system("ls") << endl;;
    return 0;
}

$ g++ b4_system.cpp 
A1/3$ ./a.out | head
a10_string_index.cpp
a11_decimal_to_hex.cpp
a1_using.cpp
a2_string_init.cpp
```





## OS 命令仿写


### 仿写 cat 命令

```
#include<iostream>
using namespace std;

// 模仿linux命令 cat

/*
$ g++ -o cat2 a1_echo_file.cpp
$ ./cat2 > 2.txt
this is a book ctrl+D

$ ./cat2 < 2.txt
$ ./cat2 < a1_echo_file.cpp
*/

int main(){
    char ch;
    while( (ch=getchar() )!=EOF  ){
            putchar(ch);
    }
    //putchar('\n');
    return 0;
}
```