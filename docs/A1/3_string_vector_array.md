# 第三章 字符串、向量和数组


## 3.1 命名空间的using声明

> 推荐简单使用 `using namespace std;`

```
using namespace::name; //需要逐条声明，每个名字都需要独立的using声明。

using std::cin;
using std::cout;
using std::endl;

//后文就可以直接使用 cint, cout 而不用前缀了。
```

> 头文件不应包含 using 声明。因为头文件会包含到其他文件，会产生意外的名字冲突。

```
#include<iostream>
using namespace std;

int main(){
    using std::cout;
    using std::endl;

    cout << "hello, using" << endl;
    return 0;
}
```










## 3.2 标准库类型 string

string 定义在命名空间 std 中。本章接下来都会使用如下代码：

```
#include<string>
using std::string;
```


### 定义和初始化string对象

- 初始化字面量，除了最后的空字符外其余都拷贝到了字符串变量中。
- 如果提供的是一个数字和一个字符，则把字符重复数字次数得到的序列是初始值。

```
#include<iostream>
#include<string>
using namespace std;

int main(){
    string s1; //默认初始化，空字符
    string s2=s1; //s2 是s1的副本
    s1="c++";
    string s2_2(s1); //s2_2 是s1的副本，赋值后

    string s3="hello"; //s3是字面量值的副本
    string s3_2("hello"); //s3_2是字面量值的副本
    string s4(10, 'c'); // s4的值是10个字符c构成的字符串

    cout << "&s1=" << &s1 << ", s1=" << s1 << endl;
    cout << "&s2=" << &s2 << ", s2=" << s2 << endl;
    cout << "&s2_2=" << &s2_2 << ", s2_2=" << s2_2 << endl;
    cout << "&s3=" << &s3 << ", s3=" << s3 << endl;
    cout << "&s3_2=" << &s3_2 << ", s3_2=" << s3_2 << endl;
    cout << "&s4=" << &s4 << ", s4=" << s4 << endl;

    return 0;
}

$ g++ a2_string_init.cpp 
$ ./a.out 
&s1=0x7ffc577b7d10, s1=c++
&s2=0x7ffc577b7d30, s2=
&s2_2=0x7ffc577b7d50, s2_2=c++
&s3=0x7ffc577b7d70, s3=hello
&s3_2=0x7ffc577b7d90, s3_2=hello
&s4=0x7ffc577b7db0, s4=cccccccccc
```



#### 直接初始化和拷贝初始化

- 拷贝初始化， 使用  = :  `string s2=s1;`
- 直接初始化，不适用=: `string s2(s1);`

> 通过显式创建临时变量来 拷贝初始化: `string s3=string(5, 'a');`，更推荐直接 `string s4(5, 'a');`





### string 对象上的操作

#### 读写 string 对象

```
#include<iostream>
using namespace std;

int main(){
    string s1;
    cout << "Pleae input a string" << endl;
    cin >> s1;

    cout << "value of s1=" << s1 << endl;
    return 0;
}

$ g++ a3_string_IO.cpp 
$ ./a.out 
Pleae input a string
  this is a book
value of s1=this
```

cin 输入流到空格自动停止，所以变量s1只拿到了第一个单词。其他它开头和结尾的空格都忽略了。


一次可以输入多个字符串，空格隔开。
```
#include<iostream>
using namespace std;

int main(){
    string s1, s2, s3;
    cout << "Pleae input 3 strings, separate by blank" << endl;
    cin >> s1 >> s2 >> s3;

    cout << "value of s1=" << s1 << endl;
    cout << "value of s2=" << s2 << endl;
    cout << "value of s3=" << s3 << endl;
    return 0;
}

$ g++ a3_string_IO2.cpp 
$ ./a.out 
Pleae input 3 strings, separate by blank
 this is a book
value of s1=this
value of s2=is
value of s3=a
```


#### 读取未知数量的string 对象

```
#include<iostream>
using namespace std;

int main(){
    string word;
    cout << "Please input several string(s):" << endl;
    int i=0;
    while(cin >> word){
        i++;
        cout << i << ">>" << word << endl;
    }
    return 0;
}

$ g++ a4_string_IO_num.cpp 
$ ./a.out 
Please input several string(s):
 this is a book
1>>this
2>>is
3>>a
4>>book
^C  #最后 ctrl+C退出，否则可以继续输入若干字符串
```



#### 使用 getline 读取一整行

> `getline(cin, line)` 一直读取到换行符，不含最后那个换行符。

```
#include<iostream>
using namespace std;

int main(){
    string line;
    cout << "Please input several string(s):" << endl;
    while( getline(cin, line) ){
        cout << "Your input is: " << line << endl;
    }
    return 0;
}

$ g++ a5_string_IO_line.cpp 
$ ./a.out 
Please input several string(s):
this is a book
Your input is: this is a book
^C
```



#### string 的 empty 和 size 方法

- `line.empty()` 判断 line 字符串是否为空，返回布尔值。
- `line.size()` 返回 line 字符串的长度。

```
#include<iostream>
using namespace std;

int main(){
    string s1="";
    string s2("hello world");

    if( !s1.empty() )
        cout << "s1 size:" << s1.size() << endl;
    else 
        cout << "s1 is empty" << endl;
    
    if( !s2.empty() )
        cout << "s2 size:" << s2.size() << endl;
    return 0;
}

$ g++ a6_string_empty_size.cpp 
$ ./a.out 
s1 is empty
s2 size:11
```



#### string::size_type 类型

`size(s1)` 返回的不是 unsigned 类型，而是一个 string::size_type 类型。

```
auto len = line.size(); //len的类型是 string::size_type
```

size_type 是一个 unsigned 类型，如果混用了有符号变量，则可能产生意外结果。

> 如果n是负数，则 `s.size < n` 很可能返回 true，因为n会转为一个比较大的无符号值。

> tips: 如果一个表达式中已经有 size() 函数，就不要使用 int 了，避免混用 int 和 unsigned 可能带来的问题。

```
#include<iostream>
using namespace std;

int main(){
    string s1="hello";
    unsigned n = -8; 

    cout << "s1=" << s1 << endl;
    cout << "n=" << n << endl;
    if(s1.size() < -8)
        cout << "s1.size < -8  is true " << endl;
    return 0;
}

$ g++ a7_string_size_return.cpp 
$ ./a.out 
s1=hello
n=4294967288
s1.size < -8  is true
```




#### string 对象的比较

逐个字符的比较。


#### string 相加

可以把 string 对象相加，但是不能把 string 字面量直接相加。

```
#include<iostream>
using namespace std;

int main(){
    string s1="hello", s2="world";
    string s3=s1+" "+s2;

    //string s4="hello" + " world";
    //error: invalid operands of types ‘const char [6]’ and ‘const char [7]’ to binary ‘operator+’

    string s5="hello" + string(" world");
    cout << s5 << endl;

    return 0;
}

$ g++ a8_string_plus.cpp 
$ ./a.out 
hello world
```




### 处理 string 对象中的字符

- string 中是否包含空白
- string 对象中字母改为小写
- 查看某个字符是否出现

//todo jump, P82, pdf(108/864) 字符串函数

cctype.h 是C语言的头文件，C++推荐使用自己的 ctype 库，后者定义在命名空间 std 中。


#### 处理每个字符？使用基于范围的 for 语句

```
#include<iostream>
using namespace std;

int main(){
    string s1="hello";

    for(char s : s1){ //auto s
        cout << s << endl;
    }
    return 0;
}

$ g++ a9_string_for.cpp 
$ ./a.out 
h
e
l
l
o
```



#### 使用for语句改变字符串中的字符

例: 小写变大写。

```
#include<iostream>
using namespace std;

int main(){
    string s1="hello, world!";

    for(char s : s1){
        s = toupper(s); //not work
    }
    cout << s1 << endl;

    //需要使用引用
    for(char &ref : s1){ //ref 是 上文 s 的引用，同名
        ref = toupper(ref);
    }
    cout << s1 << endl;

    return 0;
}

$ g++ a9_string_for2.cpp 
$ ./a.out 
hello, world!
HELLO, WORLD!
```



#### 下标访问字符串

`s1[0]` 返回字符串s1的第一个字符。

```
#include<iostream>
using namespace std;

int main(){
    string s1="hi, c++";
    cout << s1 << endl;

    for(int i=0; i<s1.size(); i++){
        if(i==0)
            s1[i]=toupper(s1[i]); //首字母大写
        cout << i << "\t" << s1[i] << endl;
    }
    cout << s1 << endl;
    return 0;
}

$ g++ a10_string_index.cpp 
$ ./a.out 
hi, c++
0       H
1       i
2       ,
3        
4       c
5       +
6       +
Hi, c++
```



#### 使用下标执行随机访问

`s1[10]` 返回字符串s1的第 11 个字符。

10进制转为16进制:

```
#include<iostream>
using namespace std;

int main(){
    string hexSymbols="0123456789ABCDEF";
    cout << "Please enter some numbers between 0-15, and get their hex:" << endl;

    string result; //保存16进制结果
    string::size_type n; //保存用户输入的数

    while(cin >> n){
        if(n<hexSymbols.size()){ //忽略无效输入
            result += hexSymbols[n];
        }
    }
    cout << "Your hex is:" << result << endl;
    return 0;
}

$ g++ a11_decimal_to_hex.cpp 
$ ./a.out  #使用 回车，然后ctrl+D终止输入
Please enter some numbers between 0-15, and get their hex:
10 0 12 9 14 15   
Your hex is:A0C9EF
```











## 3.3 标准库类型 vector


































## 3.4 迭代器介绍



































## 3.5 数组



































## 3.6 多维数组






































> 2022.7.29

