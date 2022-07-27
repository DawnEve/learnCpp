# Start

## Compile on Ubuntu 20.04

```
$ cc --version
$ gcc --version
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


$ vim A1/hello.cpp
#include<iostream>
int main(){
    printf("Hello, %s!\n", "Tom");
    return 0;
}

编译
$ g++ A1/hello.cpp

执行
$ ./a.out 
Hello, Tom!
```


获取上一个命令的执行状态
```
$ echo $?
0

如果正常执行，状态是0；否则是其他值。
$ ls 
A1  a.out  changeLog.txt  docs
$ echo $?
0

$ ls xxx
ls: cannot access 'xxx': No such file or directory
$ echo $?
2
```



## g++ 的更多参数

### 指定输出文件名 -o
默认输出 a.out
```
$ g++ -o A1/hello A1/hello.cpp
$ ./A1/hello 
Hello, Tom!
```


### 指定c++版本号 -std=c++11
```
$ g++ -std=c++11 A1/hello.cpp
$ ./a.out
Hello, Tom!
```

### 发出警告 -Wall
```
$ g++ -Wall A1/hello.cpp
$ ./a.out
Hello, Tom!
```









## 标准输入输出对象

标准库定义类4个IO对象：

- cin: istream 类型，输入
- cout: ostream 类型，输出
- cerr: ostream 类型，输出警告和错误信息
- clog: ostream 类型，输出一般性信息


```
$ cat A1/io.cpp
#include<iostream>
int main(){
    std::cout << "Enter 2 numbers:" << std::endl;
    int v1=0, v2=0;
    std::cin >> v1 >> v2;
    std::cout << "The sum of " << v1 << " and " << v2 
            << " is " << v1 + v2 << std::endl;
    return 0;
}

可以使用命令行编译，或者使用vscode 自动编译和运行。现在尝试后者。

点击vscode 右上角的 Run code，无法输入数字。
找到设置选项，输入run in terminal ，勾选Whether to run code in Integrated Terminal.
暂停: ctrl+alt+M
再次点击 Run code:

Enter 2 numbers:
5 6
The sum of 5 and 6 is 11
```


### endl

`<< std::endl;` 表示把缓存区的内容刷新到设备中。

```
// 可以写成一行
std::cout << "Enter 2 numbers:" << std::endl;

// 也可以写成多行，效果一样。
std::cout << "Enter 2 numbers:";
std::cout << std::endl;
```


### 命名空间

`std::cout` 表示从命名空间 std 中获取函数 cout。 也可以写作

```
using namespace std;
cout << "hello" << endl;
```









## 注释

单行注释 // xx

多行注释 /* xx */










## 控制流

### while 语句
```
$ vim A1/a3_while.cpp
#include<iostream>
using namespace std;

// 计算 1+2+3+...+100
int main(){
    int sum=0, i=0;
    while (i<=100){
        sum+=i;
        i++;
    }
    cout << "sum of 1+2+...+100=" << sum << endl;
    return 0;
}

$ g++ A1/a3_while.cpp 
$ ./a.out 
sum of 1+2+...+100=5050
```


### for 语句

```
$ cat A1/a4_for.cpp
#include<iostream>
using namespace std;

// 计算 1+2+3+...+100
int main(){
    int sum=0;
    for(int i=0; i<=100; i++){
        sum+=i;
    }
    cout << "(for)sum of 1+2+...+100=" << sum << endl;
    return 0;
}

$ g++ A1/a4_for.cpp 
$ ./a.out 
(for)sum of 1+2+...+100=5050
```



### 读取数量不定的输入值

输入后无法计算怎么办？哪里错了？
```
$ cat A1/a5_input_some.cpp
#include<iostream>
using namespace std;

int main(){
    int sum=0, i=0;
    cout << "Input some numbers;" << endl;
    while(cin >> i){
        sum+=i;
    }
    cout << "Sum of these values are " << sum << endl;
    return 0;
}

$ g++ -std=c++11 A1/a5_input_some.cpp
```


> 错误：这里怎么回车都不计算结果，怎么办？
> https://cplusplus.com/forum/beginner/13224/

只有在输入不是整数时才终止，空格和回车跳过。

或者专门输入 行结束符：Linux下输入 ctrl+D，注意是大写D。

```
$ ./a.out  
Input some numbers;
1 2 3 a 
Sum of these values are 6
```




### 常见的错误

编译器可检查的错误
- 语法错误: 语句末尾分号写成冒号，漏掉了一半引号，语句末尾漏掉分号等。
- 类型错误: 声明的是int，传了一个字符串。
- 声明错误: 来自标准库的名字忘了加std::前缀，标识符拼写错误。

应对办法：
- 经常编译，看错误提示。`编辑 - 编译 -调试`(edit-compile-debug)周期





### if 语句

输入一串数字，统计出相同数字连续出现的次数。

```
$ cat A1/a6_if.cpp 
#include<iostream>
using namespace std;

int main(){
    int val, curVal, count;
    while(cin >> curVal){
        count=1;
        while(cin >> val){
            if(val == curVal){
                count++;
            }else{
                cout << "Value " << curVal << " occured " << count << " times" << endl;
                curVal=val;
                count=1;
            }
        }
        cout << "Value " << curVal << " occured " << count << " times" << endl;
    }
    return 0;
}

$ g++ A1/a6_if.cpp 
$ ./a.out 
10 20 20 30 30 30 a
Value 10 occured 1 times
Value 20 occured 2 times
Value 30 occured 3 times
```








## 类简介

需要注意的报错: 

- class XX(); 后面要有分号;
- std::string a="xx" 才是对的，不能省略前缀 std::



### 类的定义和实现写到一个文件中

类名 Sales_item, 头文件 Sales_item.h中定义这个类。 //todo 定义类的加法

```
$ cat A1/a7_book/Book.h
using namespace std;

class Book{
  private:
    string isbn="";
    float price=0;
    int num=0;

  public:
    Book(string isbn, float price, int num){
      this->isbn=isbn;
      this->price=price;
      this->num=num;
    };
    string getIsbn(){ return isbn; };
    float getPrice(){ return price; }
}; //end of class


$ cat A1/a7_book/totalPrice.cpp
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


$ g++ -std=c++11 A1/a7_book/totalPrice.cpp 
$ ./a.out 
>>>Price of this book is: $90.8
```



### 类的定义和实现分别写到.h和.cpp文件中

写法2：头文件中仅仅有类方法的定义，把实现写到另一个单独的cpp文件中。

文件1，在头文件中定义类: Circle.h
```
#ifndef CIRCLE_H
#define CIRCLE_H

class Circle{
  private:
    double r;
  public:
    Circle();
    Circle(double R);
    double Area();
};

#endif
```


文件2，实现类的方法： Circle.cpp，引入头文件，并给出类的实现。
```
#include "Circle.h"

Circle::Circle(){
    this->r=0.5;
}

Circle::Circle(double R){
    this->r=R;
}

double Circle::Area(){
    return 3.14*r*r;
}
```


文件3，使用该类的文件 calc.cpp，只需要引用类的头文件
```
#include<iostream>
#include "Circle.h"

using namespace std;

int main(){
    Circle c=Circle(4);
    cout << "Area = " << c.Area() << endl;
    return 0;
}
```

需要分段编译:
```
先编译库
$ g++ -c A1/a9_Circle/Circle.cpp -o Circle.o

再编译和链接主函数
$ g++ A1/a9_Circle/calc.cpp Circle.o
$ ./a.out 
Area = 50.24
```

而有些IDE已经能自动实现以上功能： https://blog.csdn.net/weixin_66526635/article/details/123569941


或者指定两个cpp文件
```
$ g++ A1/a9_Circle/Circle.cpp A1/a9_Circle/calc.cpp -o main
$ ./main 
Area = 50.24


两个文件的顺序不重要：
$ g++ A1/a9_Circle/calc.cpp A1/a9_Circle/Circle.cpp -o main
$ ./main 
Area = 50.24
```
