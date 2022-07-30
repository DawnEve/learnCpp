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
































## 3.6 多维数组






































> 2022.7.29

