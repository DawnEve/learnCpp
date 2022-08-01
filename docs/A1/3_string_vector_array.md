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

empty() 和 size() 方法与 string 相同。后者的返回类型是vector定义的size_type类型，但是也要由元素的类型决定： 
```
vector<int>::size_type //正确
vector::size_type //错误
```

- v.empty() 返回v是否为空
- v.size() 返回v中元素个数
- v.push_back(item)  把元素 item 添加到v的末尾
- v[n] 返回v中第n个元素上元素的引用
- v1 = v2 //v2中元素的拷贝替换v1中的元素
- v1={a,b,c...} //用列表中元素替换v1中的元素
- v1 == v2 // v1和v2相等，当且仅当其元素数量相同且对应位置的元素的值也相同
- <, <=, >, >= //以字典顺序进行比较


#### 遍历vector元素 
- 操作vector中的每个元素，需要用引用: `for(auto &i : v){ i *= i; }`
- 仅仅打印 `for(auto i : v ){ cout << i << endl;}`

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> v{1,3,5,7,9};
    for(auto &i : v) //注意 i 是一个引用。
        i *= i; // 对每个i的元素求平方
    
    for(auto i : v) //遍历每个元素，并打印
        cout << i << " ";
    cout << endl;

    return 0;
}

$ g++ b5_vector_for.cpp 
$ ./a.out 
1 9 25 49 81
```



#### 计算 vector 内对象的索引

- 和 string 一样，下标从0开始，可以使用下标取对象。
- 一般也能像下标运算符返回的元素赋值，如果不是常量。
- 下标的类型是对应的 size_type 类型。


例: 统计学生成绩在0-100之间落到每10分的区间的个数，比如0-9, 10-19, ..., 100 共11个区间（最后一个区间就只有100一个取值）。 

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<unsigned> scores(11, 0); //11个段位，全部初始化为0
    unsigned grade; //得分
    cout << "Please input some scores from 0 to 100:" << endl;
    while(cin >> grade)
        if(grade <= 100)
            ++scores[grade/10];
    // output result
    for(int i=0; i<scores.size(); i++)
        cout << scores[i] << "  ";
    cout << endl;
    return 0;
}

$ g++ b6_vector_StuScore.cpp
$ ./a.out # 回车，然后 ctrl+D
Please input some scores from 0 to 100:
42 65 95 100 39 67 95 76 88 76 83 92 76 93
0  0  0  1  1  0  2  3  2  4  1 
```



#### 不能用下标添加元素

```
$ cat b7_vector_add.cpp
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> iVec; //声明空vector
    //iVec[0]=12; //编译通过，运行时 Segmentation fault (core dumped)

    //正确的做法是使用 push_back() 方法添加
    iVec.push_back(12);

    return 0;
}
```

> vector 对象 （以及 string 对象）的下标运算符可以访问已存在的元素，不能用于添加元素。

> 即使是访问，也要确保有这个元素，用下标访问一个不存在的元素，会导致一个运行时错误。怎么避免？就是尽可能使用 `范围for语句`。


习题：初始化10个元素，值都是42，给出3种实现，哪种最好？
```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    //方法1: 最好
    vector<int> ivec1(10, 42);

    //方法2
    vector<int> ivec2{42,42,42,42,42,42,42,42,42,42};

    //方法3
    vector<int> ivec3(10);
    for(int &i : ivec3)
        i=42;
    
    //输出检查
    for(int i: ivec1)
        cout << i << " ";
    cout << endl;
    
    return 0;
}

$ g++ b8_vector_init_methods.cpp  #需要修改最后一个for，反复输出这三个vector
$ ./a.out 
42 42 42 42 42 42 42 42 42 42
```











## 3.4 迭代器介绍

- 访问string 或者 vector 的元素的方法，除了下标，还有 迭代器(iterator)。
- 标注库中，包含 vector 等几个容器，都支持迭代器，但是只有少量几种才支持下标运算符。
- string 不属于容器，但是它支持很多与容器类似的操作，比如下标运算符、迭代器。

类似指针类型，迭代器也提供了对对象的间接访问。


### 使用迭代器

```
// 由编译器决定b和e的类型
// b表示v的第一个元素，e表示v尾元素的下一个位置
auto b=v.begin(), e=v.end(); //b和e的类型相同
```

- end() 返回的是一个指向尾元素的下一个位置的迭代器。
- 如果容器为空，则begin() 也返回指向尾后下一个位置的迭代器，和 end()返回的是同一个迭代器。

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> iVec(5, 0); //5个元素，值都是0(可省略)
    for(int i=0; i<iVec.size(); i++)
        iVec[i]=i; //赋值 [0, 4]

    //b表示第一个元素，e表示最后一个元素
    auto b=iVec.begin(), e=iVec.end(); //类型由编译器确定

    cout << *b << endl; // *iter 返回迭代器所指元素的引用
    cout << *(--e) << endl; //尾元素的下一个位置，往上移1，就是最后一个元素
    return 0;
}

$ g++ b9_iterator_1.cpp 
$ ./a.out 
0
4
```




#### 迭代器运算符

- 如果2个迭代器指向相同的元素，或者都是同一个容器的尾后迭代器，则它们相等，否则不等。

- *iter 返回迭代器 iter 所指元素的引用
- iter->mem 解引用iter并获取该元素的名为 mem 的成员，等价于 (*iter).mem
- ++iter 令 iter 指示容器的下一个元素
- --iter 令 iter 指示容器的上一个元素
- iter1 == iter2 判断两个迭代器是否相等：如果指向同一个元素或者它们是同一个容器的尾后迭代器，则相等，否则不等。
- iter1 != iter2

例: 字符串首字母大写
```
#include<iostream>
#include<string>
using namespace std;

int main(){
    string s2("hello c++");
    cout << "&s2=" << &s2 << endl;
    char &ref=s2[0];
    //cout << "s2[0]=" << s2[0] << ", &(s2[0])=" << &(s2[0]) << endl;
    cout << "s2[0]=" << s2[0] << ", ref=" << ref << ", &ref=" << &ref << endl;
    if( s2.begin() != s2.end()){ //确保非空
        auto it = s2.begin(); //it 指向s2的第一个首字母
        *it = toupper(*it);
        cout << "&it=" << &it << ", *it=" << *it << endl;
    }
    // 输出结果
    cout << s2 << endl;
    return 0;
}

// 字符串首字符的地址，和指向第一个字符迭代器不一样，正好差了16

$ g++ b10_iterator_captal.cpp 
$ ./a.out 
&s2=0x7ffce804cc70
s2[0]=h, ref=h, &ref=hello c++
&it=0x7ffce804cc60, *it=H
Hello c++
```



#### 将迭代器从一个元素移动到另一个元素

- end() 返回值不是指向一个元素，所以不能解引用。但是可以做 递减 操作。
- begin() 返回值可以解引用，或递增、递减操作。

例: 使用for循环和迭代器遍历字符串
```
#include<iostream>
using namespace std;

//第一个单词大写
int main(){
    string s2="hello world!";
    for(auto it=s2.begin();  it != s2.end() && !isspace(*it);  ++it){
        *it = toupper(*it);
    }
    //输出
    cout << s2 << endl;
    return 0;
}

$ g++ b11_iter_for.cpp 
$ ./a.out 
HELLO world!
```

> 注意：上文for循环使用了 `!=`, 这是因为C++标准库提供的所有容器都提供了迭代器风格，但是只有个别提供了下标访问符。




#### 迭代器类型

一般来说，我们无需知道迭代器的精确类型。

- 拥有迭代器的标准库类型使用 iterator 和 const_iterator 来表示迭代器类型。
- const_iterator 和常量指针差不多，只能读取。
  * 如果 string 或 vector 是常量，则只能使用 const_iterator；
  * 如果 string 或 vector 不是常量，则使用哪个类型迭代器都可以。


```
vector<int>::iterator it; // it 能读写 vector<int> 的元素
string::iterator it2; //it2 能读写 string 对象中的字符

vector<int>::const_iterator it3; //it3 只能读元素，不能写元素
string::const_iterator it4; //it4 只能读字符，不能写字符
```

迭代器 这个名词的三个含义:
- 迭代器概念本身
- 容器定义的迭代器类型
- 某个迭代器对象

重要的是概念，迭代器能支持一套操作，让我们从一个元素移动到另一个元素。容器定义一个 iterator 类型，该类型支持迭代器概念所规定的的一套操作。



#### begin 和 end 运算符

```
vector<int> v;
const vector<int> cv;

auto it1=v.begin(); //it1 的类型是 vector<int>::iterator
auto it2=cv.begin(); //it2 的类型是 vector<int>::const_iterator
```

如果只读，特意需要 const_iterator怎么办？C++11提供了 cbegin 和 cend 新函数。

```
auto it3 = v.cbegin(); //it3 的类型是 vector<int>::const_iterator
```



#### 结合 解引用 和 成员访问操作

- 检查当前迭代器指示的元素是否为空：`(*it).empty()`, 其中的圆括号是必须的。
- 为了简化，C++11 定义了 `箭头运算符(->)` ，结合了解引用和成员访问。`it->mem` 等价于 `(*it).mem`


//todo debug, P98, pdf124/864  报错, 不懂。懂了。
```
#include<iostream>
#include<string>
using namespace std;

int main(){
    string text="this is a book.";
    //使用迭代器遍历读，直到遇到空格停止
    for(auto it=text.cbegin();
        //it != text.cend() && !it->empty(); 
        it != text.cend() && (*it).empty(); 
        ++it){
        cout << *it << endl;
    }

    return 0;
}

$ g++ b12_iter_cbegin.cpp
编译报错，代码和书上一样。
error: request for member ‘empty’ in ‘it.__gnu_cxx::__normal_iterator<const char*, std::__cxx11::basic_string<char> >::operator*()’, which is of non-class type ‘const cha’
   10 |         it != text.cend() && (*it).empty();
```


修正版: 每个字符串结尾换行
```
// fix: char 没有 empty 方法。需要把 text 改为 vector<string> 类型
    vector<string> text={"this is a book.", "hello, c++"};

$ g++ b12_iter_cbegin2.cpp 
$ ./a.out 
this is a book.
hello, c++

```

注意：操作的是 字符串，还是  字符串向量。

修正版2: 每个字符后面空格
```
    string text="this is a book.";
    // v3: 基于 range-for 的迭代输出
    //遍历，直到遇到空格停止
    for(auto i : text){
        if(i == ' ')
            break;
        cout << i << " ";
    }
    cout << endl;

$ g++ b12_iter_cbegin3.cpp 
$ ./a.out 
t h i s
```


#### 某些对vector 的操作会使迭代器失效

> for 循环中不能向 vector 对象中添加元素。

> 但凡使用迭代器的循环体，都不要向迭代器所在的容器添加元素。







### 迭代器运算

- 迭代器递增、递减每次移动一个元素。
- 可以使用 == 或 != 比较两个迭代器。

string 和 vector 提供更多 迭代器运算：一次移动跨多个元素、迭代器的关系运算。

- iter+n //迭代器向后移动n个位置，结果还是迭代器。
- iter-n //迭代器向前移动n个位置，结果还是迭代器。
- iter1 += n // 迭代器加法，把 iter1+n 的结果赋值给 iter1
- iter1 -= n // 迭代器加法，把 iter1-n 的结果赋值给 iter1
- iter1 - iter2 //两个迭代器之间的距离，两个迭代器必须指向同一个容器中的元素或者其末尾
- >, >=, <, <= //迭代器关系运算符。两个迭代器必须指向同一个容器中的元素或者其末尾


#### 迭代器的算术运算

比如，v1 有20个元素， v1.size()/2 是10，也就是 mid=v1.begin()+10, 下标从0开始，也就是元素 v1[10]。

```
// 获取v1中间元素的迭代器
auto mid=v1.begin() + v1.size()/2;

//比较两个迭代器的前后关系
if(v1 < mid)
    // 处理 v1 前半部分的元素
```

迭代器相减，得到的类型是 difference_type 的带符号整数，有位有正有负。


#### 使用迭代器运算

迭代器二分搜索。

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> ivec={-20,0,8,10,20,50};
    auto begin=ivec.begin(), end=ivec.end();
    auto mid=begin + ivec.size()/2; //中间点

    int value = 15;
    cout << "Please input a value you want to find: [" << 
            ivec[0] << ", " << ivec[ivec.size()-1] << "]" << endl;
    cin >> value;

    // 当还没有到达终点，且还没有找到目标值时，循环
    while (mid != end && *mid!=value){
        cout << ">> value of begin, mid, end:" << *begin << ", " << *mid << ", " << *end << endl;
        if(value < *mid){
            end=mid; //为什么不需要+1
        }else{
            begin=mid+1; //为什么需要加1？
        }
        mid = begin + (end-begin)/2; //新的中点
    }
    //如果 mid==end 说明没有找到我们需要的值
    if(mid == end){
        cout << "not found" << endl;
    }else{
        cout << *mid << endl;
    }

    return 0;
}


$ g++ b13_iter_binarySearch.cpp 
$ ./a.out 
Please input a value you want to find: [-20, 50]
50
>> value of begin, mid, end:-20, 10, 1041
50
```










## 3.5 数组

数组和vector类似，但是大小不能变。

### 定义和初始化内置数组

- 数组的长度必须是已知的，也就是常量表达式。
- 数组的类型必须指定，不允许使用auto关键字让初始值去推断。
- 和vector一样，数组的元素必须是对象，因此不存在引用的数组。


```
#include<iostream>
using namespace std;

int arr0[10]; //含有10个元素的数组
//函数内的内置类型的数组，初始化时含有未定义的值。比如 arr

int main(){
    //数组的初始化
    int arr[10]; //含有10个元素的数组

    unsigned cnt=20; //不是常量表达式
    constexpr unsigned sz=25; // 常量表达式
    int *parr[sz]; //含有25个整型指针的数组

    string bad[cnt]; //报错：cnt不是常量表达式。 为啥我测试没报错呢？
    cout << "|" << bad[0] << "| length=" << bad->length()  << endl;
    cout << "|" << arr0[0] << "| outsize function, do default init " << endl;
    cout << "|" << arr[0] << "| inside function, not do default init" << endl;

    //string strs[get_size()]; //当 get_size 是 constexpr 时正确，否则错误。

    return 0;
}


$ g++ c1_array_init.cpp 
$ ./a.out 
|| length=0
|0| outsize function, do default init 
|-1031921592| inside function, not do default init
```

> 新编译器是支持变长数组的，不过很多书不建议使用变长数组。


现在C++支持变长数组，不过当使用 sizeof() 时，还是按照初始化的长度。
```
#include<iostream>
using namespace std;

int main(){
    int len=5;
    int arr[len];

    len=9;
    for(int i=0; i<len; i++)
       cout << i <<", addr=" << &(arr[i])  << "\t" << arr[i] << endl;
    
    cout << "size of arr:" << sizeof(arr) << endl;
    cout << "element number:" << sizeof(arr)/sizeof(int) << endl;
    return 0;
}

$ g++ c2_array_init.cpp 
$ ./a.out 
0, addr=0x7ffdc10861b0  -1056415296
1, addr=0x7ffdc10861b4  32765
2, addr=0x7ffdc10861b8  -951614267
3, addr=0x7ffdc10861bc  21892
4, addr=0x7ffdc10861c0  2
5, addr=0x7ffdc10861c4  0
6, addr=0x7ffdc10861c8  -951614179
7, addr=0x7ffdc10861cc  21892
8, addr=0x7ffdc10861d0  8
size of arr:20
element number:5
```


#### 显式初始化数组元素

```
#include<iostream>
using namespace std;

// 显式初始化数组
int main(){
    // 1.指定长度，并使用列表初始化
    const unsigned sz=3;
    int arr1[sz]={0,1,2}; // 含有3个元素的数组，分别是0,1,2
    
    // 2.给出数组元素，编译器根据初始值推断维度
    int arr2[]={0,1,2,3}; //维度是4的数组

    //例外1. 如果维度大，初始值个数少，则其余的默认值
    int arr3[5]={0,1,2}; //等价于 arr3[]={0,1,2,0,0}
    string arr4[3]={"this", "is"}; //等价于 arr4[]={"this", "is", ""}

    //错误: 初始值个数 大于维度则报错
    //int arr5[2]={0,1,2}; // error: too many initializers for ‘int [2]’

    cout << "size of arr2=" << sizeof(arr2)/sizeof(int) << endl;
    for(int i=0; i<sizeof(arr3)/sizeof(int); i++)
        cout << "arr3[" << i << "]=" << arr3[i] << endl;
    
    return 0;
}

$ g++ c3_array_init_explicit.cpp 
$ ./a.out 
size of arr2=4
arr3[0]=0
arr3[1]=1
arr3[2]=2
arr3[3]=0
arr3[4]=0
```



#### 字符数组的特殊性

> 字符数组，还可以采用字符串字面值进行初始化。注意字符串结尾的空字符'\0'也会被拷贝到字符串数组中。

```
#include<iostream>
using namespace std;

int main(){
    //字符串数组的 字面量初始化，字符串字面量结尾的空字符，也会被拷贝到数组中
    char a1[]={'c', '+', '+'}; //列表初始化，无空字符
    char a2[]={'c', '+', '+', '\0'}; //列表初始化，有空字符

    char a3[]="C++"; //自动添加字符串结尾的空字符，长度为4

    //const char a4[3]="C++"; //错误，没空间存放最后的空字符
    // error: initializer-string for array of chars is too long [-fpermissive]

    cout << "size of a3=" << sizeof(a3)/sizeof(char) << endl;


    return 0;
}


$ g++ c4_charArray_init.cpp 
$ ./a.out 
size of a3=4
```



#### 不允许拷贝和赋值

不能将数组的内容拷贝个其他数组作为初始值，也不能用数组为其他数组赋值(有些编译器支持数组赋值，不过这是非标准实现，不建议使用)。

```
#include<iostream>
using namespace std;

//数组初始化，不能拷贝。
// 不能用数组为其他数组赋值。
int main(){
    int a1[]={0,1,2};
    //int a2[]=a1; //error: initializer fails to determine size of ‘a2’
    
    int a2[3];
    a2=a1; //error: invalid array assignment

    return 0;
}
```



#### 理解复杂的数组声明

- 定义存放指针的数组，简单、直接。
- 定义数组的指针或数组的引用，稍微麻烦。

> 数组的声明，最好是按照结合顺序，从内向外的理解其含义。

```
#include<iostream>
using namespace std;

//数组的指针，数组的引用
int main(){

    int *ptrs[10]; //ptrs 是含有10个整型指针的数组
    //从右向左读：10个元素的数组，名字 ptrs，保存的是指针，指向的是int

    int arr[10]={0,1,2};
    //int &refs[10]=arr; //error: declaration of ‘refs as array of references

    int (*pArr2)[10] = &arr; //pArray 指向一个含有10个整数的数组
    // 由内向外读更好理解，按结合性顺序： 
    //    *pArr 是一个指针； 
    //    接着看右边，指向一个长度为10的数组的指针；
    //    最后观察左侧，它指向int数组；
    int (&refArr3)[10] = arr; //refArr 引用一个含有10个整数的数组
    // 同上
    // &refArr 是一个引用
    // 看右侧，引用对象是一个长度10的数组
    // 看左侧，数组中元素是int

    cout << "&arr  =  " << &arr << endl;
    cout << "pArr2  = " << pArr2 << endl;
    cout << "refArr3= " << refArr3 << endl;

    // 更复杂的用法
    int *(&arr4)[10] = ptrs; //arr4 是数组的引用，该数组含有10个指针
    // 由内向外，
    //    圆括号内 &arr4 是一个引用，
    //    看右侧，引用的是一个长度10的数组
    //    看左侧，数组的元素是指向 int 的指针

    return 0;
}

$ g++ c6_array_ptr_ref.cpp 
$ ./a.out 
&arr  =  0x7ffdec74e070
pArr2  = 0x7ffdec74e070
refArr3= 0x7ffdec74e070
```









### 访问数组元素

- 与标准库类型 vector 和 string 一样，数组元素也能范围 for 语句或下标运算符访问。下标起始是0。
- 下标类型通常定义为 size_t 类型，机器相关的 无符号类型，足够大，定义在 `cstddef` 头文件中。对应c语言的 `csddef.h` 头文件。
- 数组大小固定，其他用法和 vector 基本类似。最好的遍历是范围for: `for (auto i : scores)`
- 程序员保证下标不越界。下标要大于等于0，小于数组大小。否则会发生运行时错误。


```
#include<iostream>
using namespace std;

// 使用数组做分段统计: 0-100 每10分一个段，共11个段，最后一个段只有100一个分数
int main(){
    unsigned scores[11]={}; //存放11个段位统计数
    unsigned grade;
    cout << "Please input some numbers [0,100]: " << endl;
    while (cin >> grade){
        if(grade<=100){
            ++ scores[grade/10];
        }
    }
    // output
    for(auto i : scores){
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

$ g++ c7_array_cut_count.cpp 
$ ./a.out #enter, ctrl+D
Please input some numbers [0,100]: 
0 100 20 95
1 0 1 0 0 0 0 0 0 1 1 
```

 例2：访问合法区域，则不报错。
 ```
 #include<iostream>
using namespace std;

//程序员保证数组下标不越界，否则运行时错误
int main(){
    int arr[3]={10,2,3};
    for(auto i : arr)
        cout << i << " ";
    cout << endl;
    // 越界的也不报错 ??
    cout << "arr[5]   =" << arr[5] << endl; //越界，访问 合法区域，不报错，只是值不确定。
    cout << "arr[5000]=" <<arr[5000] << endl; //越界，并访问非法内存区域时，才报错
    //Segmentation fault (core dumped)
    return 0;
}


$ g++ c8_array_index_outOf.cpp 
$ ./a.out 
10 2 3 
arr[5]   =0
Segmentation fault (core dumped)
```










### 指针和数组

- 数组和指针关系密切，使用数组时，编译器会把它转为指针。
- 数组名就是指向其第一个元素的指针： `string *p2=arr; //等价于 p2=&arr[0];`

例1：当数组是一个auto变量的初始值时，推断得到的类型是指针而不是数组。
```
#include<iostream>
using namespace std;

//数组作为auto变量的初始值，推断其为指针，而不是数组
int main(){
    int  arr[3]={10, 11, 12};
    auto arr2(arr); //arr 是一个数组，作为auto 类型arr2的初始值时
    //arr2=4; //error: invalid conversion from ‘int’ to ‘int*’ [-fpermis]ive
    
    //arr=4; //error: incompatible types in assignment of ‘int’ to ‘int [3]’

    cout << arr2 << endl;
    cout << *arr2 << endl;
    cout << *(arr2+1) << endl; //可以递增，获取下一个元素，因为数组在内存区是连续的

    return 0;
}

$ g++ c9_arr_as_refInit.cpp 
$ ./a.out 
0x7ffc2825b59c
10
11
```

> 上述过程 `auto arr2(arr);` 的实际初始化过程类似于 `auto arr2(&arr[0]);` 显然arr2的类型是 int *;

> 使用 decltype(arr) arr3; //返回的是由10个整数构成的数组。



#### 指针也是迭代器

- 指针支持递增、递减。 

```
int arr[]={0,1,2};
int *p=arr; //p指向arr的第一个元素
++p;  //p指向arr[1]
```


- 要使用迭代器循环，就要获取尾后迭代器，获取的方式 `int arr[10]; int *end=&arr[10];` 最后一个不存在的元素的唯一作用，就是初始化其尾后迭代器。

> 尾后指针/迭代器：不能解引用，不能递增。


```
#include<iostream>
using namespace std;

//使用迭代器遍历数组
int main(){
    int arr[3]={10, 11, 12};
    // 尾后迭代器，就是最后一个不存在的元素的地址
    int *end=&arr[ sizeof(arr)/sizeof(int) ];
    for(int *be=arr; be != end; ++be){
        cout << *be << endl;
    }
    return 0;
}

$ g++ c10_arr_iter_end.cpp 
$ ./a.out 
10
11
12
```

#### 标准库函数 begin 和 end

尾后指针容易出错，怎么办？C++11引入了 begin 和 end 函数，获取其位置。该2函数返回值是指针。

```
#include<iostream>
using namespace std;

//使用迭代器遍历数组： begin end
int main(){
    int arr[3]={10, 11, 12};
    // C++11 新引入的函数 begin 和 end，返回的指针：首位置和尾后
    int *beg=begin(arr);
    int *last=end(arr); //变量名不能和函数名同名(这里使用 last)，否则报错 ‘end’ cannot be used as a function

    int i=0;
    for(; beg != last; ++beg){
        cout << *beg;
        cout << "\t" << beg << " " << &arr[i] << " " << arr[i] << endl;
        i++;
    }
    return 0;
}

$ g++ -std=c++11 c10_arr_iter_end2.cpp 
$ ./a.out 
10      0x7ffd5767598c 0x7ffd5767598c 10
11      0x7ffd57675990 0x7ffd57675990 11
12      0x7ffd57675994 0x7ffd57675994 12
```


#### 指针运算

- 指向数组元素的指针，可以执行迭代器的所有运算：解引用、递增、比较、与整数加减、两指针的相减，意义也一致。

```
#include<iostream>
using namespace std;

//指向数组元素的指针，加减整数，表示指针前后移动
int main(){
    int arr[10]={0,1,2,3,4,5,6,7,8,9};
    int *p1=arr; //指向第1个元素 arr[0]
    int *p2=p1+4; //指向第5个元素 arr[4]

    cout << *p1 << " " << arr[0] << endl;
    cout << *p2 << " " << arr[4] << endl;

    cout << p2-p1 << endl;
    return 0;
}

$ g++ c11_arr_ptr_add.cpp 
$ ./a.out 
0 0
4 4
4
```


#### 解引用和指针运算的交互

- `int last=*(begin + 4)` 和 `int last=*begin +4` 是不同的，前者是指针移动4位后的元素值，后者是首元素的值加上数字4.


#### 下标和指针

- 数组名就是指向数组第一个元素的指针。
- 只要是指向数组元素的指针，都可以和数组名一样使用下标运算。
    * 只是要注意，下标0是当前指针位置，往前则下标为负数。

> 内置的下标运算符所用的索引值不是无符号类型，这个和 vector 和 string 不同。

```
#include<iostream>
using namespace std;

//指向数组元素的指针，可以使用下标运算符。
int main(){
    int arr[]={0,1,2,3,4,5};
    int *p1=arr;
    int *p2=p1+2;

    cout << "arr[1]=" << arr[1] << endl;
    cout << "p1[1]=" << p1[1] << endl;
    cout << "p2[1]=" << p2[1] << endl;
    cout << "p2[0]=" << p2[0] << ", *p2=" << *p2 << endl;
    cout << "p2[-1]=" << p2[-1] << endl; //下标可以为负

    return 0;
}

$ g++ c12_arr_ptr_index.cpp 
$ ./a.out 
arr[1]=1
p1[1]=1
p2[1]=3
p2[0]=2, *p2=2
p2[-1]=1
```








### C风格字符串

> 不建议使用 C风格的字符串，容易导致程序漏洞。

- 字符串字面值，最后是一个空字符'\0'，一般利用指针操作这些字符串。
- 头文件 `cstring`, 对应C语言的 `string.h`

提供了几个函数:
- strlen(p) 返回p的长度，空字符不计算在内。
- strcmp(p1, p2) 比较p1和p2的大小。相等返回0；p1>p2，返回+1；p1 < p2返回-1；
- strcat(p1, p2) 将p2附件到p1的后面，返回p1
- strcpy(p1, p2) 将p2拷贝给p1，返回p1


```
#include<iostream>
#include<cstring>
using namespace std;

//C 风格的字符串操作
int main(){
    char str1[]={'C', '+', '+'}; //不以空字符结尾
    char str2[]={'C', '+', '+', '\0'}; //以空字符结尾

    cout << strlen(str1) << endl; //返回的长度不对，也可能是一直读取到\0结束
    cout << strlen(str2) << endl; 

    return 0;
}


$ g++ c13_C_string_strlen.cpp 
$ ./a.out 
6
3
```


#### 比较字符串

- 比较标准库 string 对象，用的是普通关系运算符和相等运算符。
- 比较 C 风格字符串，则要使用 strcmp() 函数。


```
#include<iostream>
#include<cstring>
using namespace std;

// 字符串的比较
int main(){
    //1.标准库 string 类型比较
    string s1="a small dog;";
    string s2="a small cat;";

    if(s1 > s2)
        cout << s1 << " is > " << s2 << endl;
    
    //2. C 风格字面量的比较
    const char c1[]="A big dog;";
    const char c2[]="A big cat;";

    //(1) 
    if(c1 > c2) //实际比较的是2个指针，而非字符串本身
        cout << c1 << " is > " << c2 << endl;
    else
        cout << " c1> c2, else" << endl;

    //(2)相比较C风格的字符串，需要用 strcmp 函数
    if( strcmp(c1, c2)>0 ){
        cout << c1 << " is > " << c2 << endl;
    }

    return 0;
}

$ g++ c14_string_cmp.cpp 
$ ./a.out 
a small dog; is > a small cat;
 c1> c2, else
A big dog; is > A big cat;
```


#### 目标字符串的大小由调用者指定

- 连接2个字符串，如果是 string 对象，则直接用+号
- 如果是 C风格的字符串，则需要使用 strcat(p1, p2)，把p2复制到p1的结尾，还要保证p1足够大。

```
#include<iostream>
#include<cstring>
using namespace std;

// 字符串的连接
int main(){
    // 2个 string 对象的连接
    string s1="hello";
    string s2="world";
    string s3=s1+" "+ s2;
    cout << s3 << endl;

    // 2个 C 风格的字符串的连接
    char c1[]="hello";
    char c2[]="world";

    //要先声明一个大数组, 貌似估算错了也没有影响
    //char c3[500];
    char c3[5];
    strcpy(c3, c1);
    strcat(c3, " ");
    strcat(c3, c2);
    //cout << c3 << endl;
    char *p=c3;
    while(*p != '\0'){
        putchar(*p);
        p++;
    }
    putchar('\n');

    return 0;
}

$ g++ c15_string_cat.cpp 
$ ./a.out 
hello world
hello world
```




### 与旧代码的接口

#### 混用 string 对象和 C风格字符串

- 任何出现字符串字面量的地方，都可以使用以空字符'\0'结束的字符数组代替。
    * 允许使用'\0'字符数组来给string对象初始化或赋值
    * string 加法允许其中一个是'\0'结束的字符数组，不能2个都是。
- 反之不成立：程序需要C风格字符串，无法直接使用 string 对象代替。可以使用string的 `const char *s2 = s1.c_str()` 方法。
    * 执行完 c_str() 获取的字符串，如果原始 s1 改变了，则 返回的 s2 也跟着变。


```
#include<iostream>
using namespace std;

// string 对象给 C风格字符串赋值
int main(){
    string s1="hello, world!";

    //char *s2=s1;
    // error: cannot convert ‘std::string’ {aka ‘std::__cxx11::basic_string<char>’} to ‘c in initialization

    //char *s3=s1.c_str(); //error: invalid conversion from ‘const char*’ to ‘char*’ [-fpermissive]

    const char *s4=s1.c_str(); //一个指针，指向char的指针，指向的元素不能变更
    //s4[0] ='H'; //error: assignment of read-only location ‘* s4’
    
    //首字母大写
    s1[0]='H'; 
    cout << s4[0] << endl;
    cout << s4 << endl;

    // 指向第二个元素
    s4=&s1[1];
    cout << s4 << endl;

    // 如果改变了原始 string 字符串
    s1="ni hao";
    cout << s4 << endl;

    return 0;
}


$ g++ c16_string_c_str.cpp 
$ ./a.out 
H
Hello, world!
ello, world!
i hao
```



#### 使用数组初始化 vector 对象

- 可以使用数组为vector 对象初始化。只需要拷贝区域的 首元素地址 和 尾后地址 即可。

```
#include<iostream>
#include<vector>
using namespace std;

//使用数组初始化 vector
int main(){
    int arr[]={0,1,2,3,4,5};

    //2个初始化 vector，分别是数组的头指针和尾后指针
    vector<int> ivec(begin(arr), end(arr));
    
    //遍历1
    for(auto i : ivec)
        cout << i << " ";
    cout << endl;

    // 使用其他指针初始化 vector: arr[1], arr[4]
    vector<int> ivec2( &arr[1], arr+4);

    //遍历2
    for(int i=0; i<ivec2.size(); i++)
        cout << ivec2[i] << " ";
    cout << endl;

    return 0;
}

$ g++ c17_arr_init_vector.cpp 
$ ./a.out 
0 1 2 3 4 5 
1 2 3
```

> 建议：尽量使用标准库类型，而非数组。

- 指针和数组容易出错，概念和声明都易错。
- 现代c++程序应尽量用vector 和迭代器，避免使用内置数组和指针。
- 应该尽量使用 string，避免使用 C 风格的基于数组的字符串。


















## 3.6 多维数组

- c++中的多维数组，就是数组的数组。

//todo jump, P112, pdf138/864






















> 2022.7.29
> 2022.8.1 almost over;
