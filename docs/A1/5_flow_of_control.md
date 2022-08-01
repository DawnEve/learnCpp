# 第五章 语句



## 5.1 简单语句

空块等价于空语句。




## 5.2 语句作用域

- 在 if, switch, while 和 for 语句的控制结构内定义的变量，只在内部可见。

```
#include<iostream>
using namespace std;

int get_num(){
    int x;
    cin >> x;
    return x;
}

// 变量在控制结构内的定义，只在内部可见
int main(){
    cout << "Please input some numbers, exit when <0:" << endl;
    //1. while
    while(int i = get_num() ){
        cout << i << endl;
        if (i<0)
            break;
    }
    //i=1; //error: ‘i was not declared in this scope
    return 0;
}

$ g++ a1_scope.cpp 
$ ./a.out 
Please input some numbers, exit when <0:
1 2 4 -1
1
2
4
-1
```


如果其他代码也需要访问控制变量，则变量必须定义在语句外部：
```
#include<iostream>
#include<vector>
using namespace std;

// 其他地方需要的，需要定义在局部之外
int main(){
    vector<int> arr={1,2,3,-5,7};

    //寻找第一个负数
    auto beg=arr.begin();
    while(beg != arr.end() && *beg>=0){
        ++beg;
    }
    if(beg == arr.end()){
        cout << "not found" << endl;
    }else{
        cout << *beg << endl;
    }

    return 0;
}


$ g++ a2_scope_outside.cpp 
$ ./a.out 
-5
```









## 5.3 条件语句

### if else
- C++ 规定，else 与最近的尚未匹配的if匹配，从而消除程序的歧义。
- 为了防止和期望不同，建议多加花括号。




### switch 语句

- `switch(keyword) (case value1:)`: 适合于有整型结果的分支，比如 char 和 int。
- 每个 case 都要有 break 语句，否则会顺序执行。
- 不符合任何一个case的，自动匹配 `default:` 分支。


```
#include<iostream>
using namespace std;

// switch 语句统计元音字母频率
int main(){
    unsigned aCnt=0, eCnt=0, iCnt=0, oCnt=0, uCnt=0, Cnt=0;
    char ch;
    while (cin >> ch){
        // 如果 ch 是元音字母，将其对应的计数器加1
        switch(ch){
            case 'a':
                ++aCnt;
                break;
            case 'e':
                ++eCnt;
                break;
            case 'i':
                ++iCnt;
                break;
            case 'o':
                ++oCnt;
                break;
            case 'u':
                ++uCnt;
                break;
            default:
                ++Cnt;
        }
    }
    //output:
    cout << "Number of vowel a: " << aCnt << '\n'
        << "Number of vowel e: " << eCnt << '\n'
        << "Number of vowel i: " << iCnt << '\n'
        << "Number of vowel o: " << oCnt << '\n'
        << "Number of vowel u: " << uCnt << '\n'
        << "Number of all chars: " << Cnt << '\n'
        << endl;
    return 0;
}

$ g++ a3_switch.cpp 
$ ./a.out 
this is a book
Number of vowel a: 1
Number of vowel e: 0
Number of vowel i: 2
Number of vowel o: 2
Number of vowel u: 0
Number of all chars: 6
```


例: 只统计元音字母总数。
```
#include<iostream>
using namespace std;

//没有break，则case每个分支都会执行到
int main(){
    unsigned vowelCnt=0, others=0;
    char ch;
    // 忽略掉了空白字符
    while(cin >> ch){
        switch(ch){
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                ++vowelCnt;
                break;
            default:
                cout << ch;
                ++others;
        }
    }
    cout << endl;

    cout << "the number of vowel:" << vowelCnt << endl;
    cout << "the number of other chars:" << others << endl;
    return 0;
}

$ g++ a4_switch_no_break.cpp 
$ ./a.out  #回车，ctrl+D
this is a book
thssbk
the number of vowel:5
the number of other chars:6
```

























## 5.4 迭代语句

### while 语句

> 定义在while 条件部分或者循环体内的变量，每次迭代都经历从创建到销毁的过程。


### 传统 for 语句

```
for(init; condition; expression){
    statement;
}
```



### 范围 for 语句

C++11 引入的更简单的 for 语句。

```
for(declaration:: expression){
    statement;
}
```

例：对向量的每个元素都乘以2。
```
#include<iostream>
#include<vector>
using namespace std;

// range -for
int main(){
    vector<int> vec={0,1,2,3,4,5};
    // 写时，必须是引用
    for(auto &i : vec){
        i=i*2;
    }
    //读时，不做要求
    for(auto i : vec){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}

$ g++ a5_range_for.cpp 
$ ./a.out 
0 2 4 6 8 10
```


范围for循环来源于与之等价的传统for循环：
```
#include<iostream>
#include<vector>
using namespace std;

// range -for, 与之等价的 传统 for 
int main(){
    vector<int> vec={0,1,2,3,4,5};
    // 写时，必须是引用
    for(auto &i : vec){
        i=i*2;
    }
    //等价的传统 for 循环
    for(auto beg=vec.begin(), end=vec.end(); 
        beg!=end; 
        ++beg){
        auto &ref=*beg; //ref 是 beg迭代器指向的值的引用，这样才能执行写操作
        ref *= 2;
    }

    for(auto i : vec)
       cout << i << " ";
    cout << endl;
    return 0;
}

$ g++ a5_range_for2.cpp 
$ ./a.out 
0 4 8 12 16 20
```

> 看上例可知：范围for不能在循环内部增加vector对象的元素，因为范围for依赖尾后迭代器，增删元素可能使 end 函数值变得无效。




### do while 语句

- 执行执行一次函数体，其余和 while 一样。

```
do{
    stagement;
}while(condition);
```

> 注意 do while 最后的条件后面必须有分号结尾。














## 5.5 跳转语句

- break 跳出本循环。
- continue 终止本次循环，并继续下一个循环迭代。
- goto 语句，不要使用，忘掉它！













## 5.6 try 语句块和异常处理

- 典型的异常处理包括：市区数据库连接、遇到意外输入等。
- 处理反常行为，可能是设计所有系统中最难的一部分。

c++ 语言中，异常处理包括：
- throw 表达式(throw expression)，异常检测部分使用 throw 表达式表示它遇到了无法处理的问题。我们说 throw 引发(raise) 了异常。
- try 语句块(try block)，异常处理部分使用try语句块处理异常。try语句块以关键词try开始，并以一个或多个catch子句(catch clause)结束。try语句块中代码跑出的异常通常会被某个 catch 子句处理。因为 catch 子句“处理”异常，所以他们也被称为 异常处理代码(exception handler)。
- 一套异常类(exception class)，用于在 throw 表达式和相关 catch 子句之间传递异常的具体信息。


### throw 表达式

```
#include<iostream>
using namespace std;

// 抛出异常
int main(){
    int a, b;
    cout << "Please input 2 int:" << endl;
    cin >>a >> b;
    if(b==0){
        throw runtime_error("must not be devided by 0");
    }

    //如果执行到这里，说明b不等于0
    cout << a/b << endl;
    
    return 0;
}


$ g++ b1_throw.cpp 
$ ./a.out 
Please input 2 int:
10 2
5

$ ./a.out  #故意错误呢？
Please input 2 int:
10 0
terminate called after throwing an instance of 'std::runtime_error'
  what():  must not be devided by 0
Aborted (core dumped)
```


- runtime_error 是标准库异常类的一种，定义在 stdexcept 头文件中。
- 我们必须初始化该对象，方式是给它提供一个string对象或者C风格的字符串。







### try 语句块

- try 后跟着一个或多个 catch 语句。
- try 语句块中声明的变量在块外无法访问，特别是在 catch 子句也无法访问。

```
try{
    program-statement;
} catch(exception-declaration){
    handler-statement
} catch(exception-declaration){
    handler-statement
} //...
```


#### 编写处理的代码

> 处理异常，就是保证出现错误，程序还能继续运行。

```
#include<iostream>
using namespace std;

// try 处理异常
int main(){
    int a, b;
    while(1){
        cout << "Please input 2 int:" << endl;
        try{
            cin >>a >> b;
            if(b==0){
                throw runtime_error("must not be devided by 0");
            }

            //如果执行到这里，说明b不等于0
            cout << a/b << endl;
        }catch (runtime_error err){
            cout << err.what()
                << "\n Try again? Enter y or n" << endl;
                char c;
                cin >> c;
                if(! cin || c=='n'){
                    break; //跳出while 循环
                }
        }
    }
    
    return 0;
}


$ g++ b2_try_catch.cpp 
$ ./a.out 
Please input 2 int:
10 2
5
Please input 2 int:
10 0
must not be devided by 0
 Try again? Enter y or n
y
Please input 2 int:
10 5
2
Please input 2 int:
10 0
must not be devided by 0
 Try again? Enter y or n
n
```


#### 函数在寻找处理代码的过程中退出

复杂系统中，程序遇到抛出异常的代码前，其执行路径可能已经经过了多个 try 语句块。
- 例如一个try语句块可能调用了包含另一个try语句块的函数，新的try语句块可能调用了包含有一个try语句块的新函数，等等。


如果有try，就找catch，如果找不到，最终调用 terminate 的标准库函数，导致程序非正常退出。

如果没有try，则直接执行 terminate 非正常退出当前程序。



> 提示：编写异常安全(exception safe)的代码非常困难！该部分超出了本书的范围。
> 异常中断了程序的正常流程。








### 异常标准

C++ 的异常类分别定义在4个头文件中：

- exception 头文件，最通用的，只报告异常的发生，不提供任何额外信息。
- stdexcept 头文件，定义了几种常见的异常，见下表， P176
- new 头文件定义了 bad_alloc 异常类型，P407
- type_info 头文件定义了 bad_cast 异常类型, P731


- exception 最长先的问题
- runtime_error 只在运行时才能检测到的问题
- range_error 运行时错误：生成的结果超出了有意义的值域范围

//todo jump, P176, pdf(202/864)





> 2022.8.1