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

C++ 既有 类模板(class template), 也有函数模板，其中 vector 是一个类模板。

只有对 C++ 有很深的理解才能写出模板，第16章学习自定义模板。但是使用很简单。

接下来需要如下代码：
```
#include<vector>
using std::vector;
```

编译器根据模板创建类或函数的过程，叫做实例化(instantiation)。


对于类模板，需要提供信息指定模板到底实例化为什么样的类。需要提供的信息由模板决定。
- 提供信息的方式：模板名字后加尖括号，括号内放上信息。

```
vector<int> ivec; //ivec 保存的是 int 类型的对象
vector<Book> Book_vec; //Book_vec 保存的是 Book 类型的对象
vector<vector<string>> file; //该向量的元素是vector元素
```

> 注意：元素是vector的向量，新老标准略有不同，老标准要求外层右尖括号前要有一个空格，`vector<vector<int> >`, 而C++11则可以去掉该空格 `vector<vector<int>>`



### 定义和初始化 vector 对象

```
$ cat b1_vector_1.cpp
#include<iostream>
#include<vector>
using namespace std;

// 初始化 vector 对象的方法
int main(){
    vector<int> v1;  //v1 是一个空vector，它的潜在元素是int类型，执行默认初始化
    vector<int> v2(v1); //v2 中包含 v1的所有元素的副本
    vector<int> v2_2=v1; //等价于 v2(v1) ，v2 中包含v1所有元素的副本
    vector<int> v3(5, 12); //v(n, val) v3包含n个重复的元素，每个元素的值都是val
    vector<int> v4(5); //v(n) v4中包含了n个执行了值初始化的对象
    vector<int> v5{1,2,3,10}; //v(a,b,c...)  v5包含了初始值个数的元素，每个元素被赋予相应的初始值
    vector<int> v5_2={1,2,3,20}; //等价于 v(a,b,c...)
    
    vector<vector<int>> iVec2;
    return 0;
}
```

#### 列表初始化vector对象

C++11新标准，另一种为 vector 对象的元素赋初始值的方法，列表初始化：花括号括起来的0个或多个元素值给vector赋值。

- vecter 的元素个数: `ivec.size()`

```
$ cat b2_vector_string.cpp
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<string> svec; //默认初始化，svec不含任何元素。
    // 最常见的方式：先定义一个空vector，运行时获取到的元素的值后再逐一添加

    // 列表初始化
    vector<string> vs1={"this", "is", "a", "book"}; 
    vector<string> vs2{"this", "is", "a", "book"};
    //vector<string> vs3("this", "is", "a", "book"); //报错：不能使用圆括号

    // 遍历容器中的元素
    for(int i=0; i<vs1.size(); i++)
        cout << i << " " << vs1[i] << endl;

    return 0;
}

$ g++ b2_vector_string.cpp 
$ ./a.out 
0 this
1 is
2 a
3 book
```


#### 创建指定数量的元素

```
vector<int> ivec(10, -1); //10个int类型的元素，每个都被初始化为-1
vector<string> svec(10, "hi!"); //10个string类型的元素，每个都被初始化为"hi!"
```


#### 值初始化

- 只提供数量，略去初始值，则库会创建一个 值初始化的元素初值，并赋值给容器的每个元素。该值由元素的数据类型决定。

```
vector<int> ivec(10); //10个元素，每个都初始化为0
vector<string> svec(10); //10个元素，每个都是空string对象
```


#### 列表初始值or 元素个数？

//todo








### 向 vector 对象中添加元素

列表直接初始化适用于三种情况：

- 初始值已知且数量较少
- 初始值是另一个vector对象的副本
- 所有元素的初始值都一样

更常见的是不确定元素个数，初始值也不同。

- `v.push_back(item)` 向vector v的末尾添加元素item

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    // v.push_back(item) 在v的末尾添加元素item
    vector<int> ivec; //空vector对象
    cout << "length:" << ivec.size() << endl;

    for(int i=0; i<=5; i++){
        ivec.push_back(i); //把每个i放到ivec的末尾
    }
    cout << "length:" << ivec.size() << endl;

    //输出
    for(int i=0; i<ivec.size(); i++)
        cout << i << " " << ivec[i] << endl;
    
    return 0;
}

$ g++ b3_vector_push_back.cpp 
$ ./a.out 
length:0
length:6
0 0
1 1
2 2
3 3
4 4
5 5
```


例: 读入不定个数的字符串

```
#include<iostream>
#include<vector>
using namespace std;

// 读入不定个数的字符串

int main(){
    // v.push_back(item) 在v的末尾添加元素item
    vector<string> line;
    string word;

    cout << "Please input some words:" << endl;
    while(cin >> word)
        line.push_back(word); 

    //输出
    for(int i=0; i<line.size(); i++)
        cout << i << " " << line[i] << endl;
    
    return 0;
}

$ g++ b3_vector_push_back2.cpp 
$ ./a.out   # 回车，然后 ctrl+D
Please input some words:
 this is a book
0 this
1 is
2 a
3 book
```

> C++ 的vector 对象能高效增长，建议先创建空 vector，然后再逐个添加。这一点和C或者Java不同，后者要求创建时指定容器容量。

> **警告**：如果循环体内部包含有向vector对象添加元素的语句，则不能使用范围for循环。






### 其他 vector 操作

- v.empty() 返回v是否为空
- v.size() 返回v中元素个数
- v.push_back(item)  把元素 item 添加到v的末尾
- v[n] 返回v中第n个元素上元素的引用
- v1 = v2 //v2中元素的拷贝替换v1中的元素
- v1={a,b,c...} //用列表中元素替换v1中的元素
- v1 == v2 // v1和v2相等，当且仅当其元素数量相同且对应位置的元素的值也相同
- <, <=, >, >= //以字典顺序进行比较




















## 3.4 迭代器介绍



































## 3.5 数组



































## 3.6 多维数组






































> 2022.7.29

