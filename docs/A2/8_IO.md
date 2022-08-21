# 8. IO 库

已经介绍过的

- istream(输入流)类型，提供输入操作
- ostream(输出流)类型，提供输出操作
- cin，一个 istream 对象，从标准输入读取数据
- cout，一个 ostream 对象，向标准输出写入数据
- cerr，一个 ostrem 对象，向标准输出写入数据
- >> 运算符，用来从一个 istream 对象读取输入数据
- << 运算符，用来向一个 ostream 对象写入输出数据
- getline 函数(P78, 3.3.2)，从一个给定的 istream 读取一行数据，存入一个给定的 string 对象中: `getline(cin, str2);`


```
#include<iostream>
using namespace std;

// getline 函数： 怎么读取一句，而不是一个单词？
// 看来是标准库函数 std::getline
string &myGetline(istream &is, string &line){
    cin >> line;
    return line;
}

int main(){
    string a1;
    cout << "a1=" << a1 << endl;
    //1
    cout << "\t1 Input a line, only get one word:" << endl;
    a1=myGetline(cin, a1);
    cout << "a1=" << a1 << endl;
    // pass当前行多余的单词
    while(getchar() !='\n' ){
        continue;
    } //空语句

    //2
    string a2;
    cout << "\t2 Input a line, get one line:" << endl;
    getline(cin, a2);
    cout << "a2=" << a2 << endl;

    return 0;
}

$ g++ a1_getline.cpp 
$ ./a.out 
a1=
        1 Input a line, only get one word:
hi, tom
a1=hi,
        2 Input a line, get one line:
hi, tom
a2=hi, tom
```






## 8.1 IO 类

- 控制台读写
- 文件读写
- 操作 string
- 读写需要宽字符支持的语言？？


> 表 8.1 IO 库类型和头文件

- iostream 头文件 定义了用于读写流的基本类型
    * 类型 istream, wistream 从流读取数据
    * 类型 ostream, wostream 向流写入数据
    * iostream, wiostream 读写流
- fstream 定义了读写命名文件的类型
    * ifstream, wifstream 从文件读取数据
    * ofstream, wofstream 向文件写入数据
    * fstream, wfstream 读写文件
- sstream 定义了读写内存 string 对象的类型
    * istringstream, wistringstream 从 string 读取数据
    * ostringstream, wostringstrem 向 string 写入数据
    * stringstream, wstringstream 读写stream

宽字符带前缀w，例如 wcin, wcout, wcerr, 分别是 cin, cout, cerr 的宽字符版对象。

- 宽字符版本的类型和对象与对应的普通 char 版本的类型定义在同一个头文件中。
- 如 fstream 头文件中，定义了 ifstream 和 wifstream 类型。




#### IO 类型间的关系

- 我们使用 >> 读取数据，不用关心是从一个控制台窗口、一个磁盘文件、一个内存string。
    * 忽略不同类型的流的差异，是通过 **继承机制(inheritance)** 实现的。见P710,18.3
    * 简单说，我们可以将一个派生类（继承类）对象当做基类(所继承的类)对象来使用。
    * ifstream 和 istringstream 都继承自 istream。也就是说，我们如何使用 cin 的，也可以同样使用前2者。
        * 例如，可以对 ifstream 或 istringstream 对象调用 getline
        * 使用>>从一个ifstream 或 istringstream 对象中读取数据。
    * 类似的，ofstream 和 ostringstream 都继承自 ostream。如何使用 cout 的，也同样使用前2者。

> Note: 本节剩余部分，标准库流特性，可无差别应用于 普通流、文件流和 string 流，以及 char 或 宽字符流版本。










### 8.1.1 IO 对象无拷贝或赋值

```
ofstream out1, out2;
out1 = out2; //错误：不能对流对象赋值
ofstream print(ofstream); //错误：不能初始化 ofstream 参数
out2 = print(out2);  //错误，不能拷贝流对象
```

- 由于不能拷贝IO对象，因此不能将形参或返回类型设置为 流类型(P188, 6.2.1)
- 进行IO操作的函数通过以引用方式传递和返回流。
- 读写一个IO对象会改变其装填，因此传递和返回的引用不能是 const 的。

```
#include<iostream>
using namespace std;

// 流不能 拷贝 或 赋值，所以以 引用方式传递和返回流

// 引用方式传参
void read(istream &is, string &str){
    getline(is, str);
}

// 返回流：过滤掉字符,
istream &filter(istream &is){
    cout << "how to filter?" << endl;
    return is;
}

int main(){
    string s2="";
    // test1
    cout << "please input one line:" << endl;
    read(cin, s2);
    cout << "s2=" << s2 << endl;
    
    // test2
    read( filter(cin), s2 );
    cout << "s2=" << s2 << endl;

    return 0;
}


$ g++ a2_stream_para_or_rerturn.cpp 
$ ./a.out 
please input one line:
a book
s2=a book
how to filter?
this is
s2=this is
```




### 8.1.2 条件状态

IO操作一个与生俱来的问题是可能发生错误。有些可以修复，有些不能修复，在系统深处，超出应用程序可以修正的范围。

- IO 类所定义的一些函数和标志，可以帮助我们访问和操作流的**条件状态(condition state)**

- 表 8.2 IO库条件状态
    * strm::iostate   strm是一种 IO 类型，见表8.1。 iostate 是一种机器相关的类型，提供了条件状态的完整功能。
    * strm::badbit 用来表示流已经奔溃
    * strm::failbit 用来指出一个 IO 操作失败了。
    * strm::eofbit 指出流到达了文件结尾
    * strm::goodbit 指出流处于错误状态。此值保证为零
    * s.eof() 若流s的eofbit 置位，则返回true
    * s.fail() 若流s的failbit或badbit置位，则返回true
    * s.bad() 若流s的badbit置位，则返回 true
    * s.good() 若流s处于有效装填，则返回true
    * s.clear() 将流s中所有条件状态为复位，将流的状态设置为有效，返回void
    * s.clear(flags) 根据给定的flags标志位，将流s中对应条件状态位置位。flags的类型为 strm::iostate。返回 void
    * s.rdstate() 返回流s的当前条件状态，返回值类型为 strm::iostate

> 置位的意思是对某一位变量置位，就是将其设为“1”。相反复位就是将其设为“0”。

下面是一个IO错误的例子：

```
int ival;
cin >> ival;
```

- 如果键入 Boo，读操作就会失败。代码期望读取一个int，但是得到一个字符B。这样 cin 会进入错误状态。
- 一个流一旦发生错误，其上后续的IO操作都会失败。
- 只有一个流处于无错状态时，我们才可以从它读取数据，向它写入数据。
- 因为流可能处于错误状态，因此代码使用流之前要检查它是否处于良好状态。

```
// 确定一个流对象的状态的最简单的方法是将它作为一个条件来使用
while(cin >> word)}{
    //ok: 读操作成功...
}
```

例: 输入int，然后判断输入是否正确

```
#include<iostream>
using namespace std;

//使用流之前，检查它是否处于良好状态：把它作为一个条件
int main(){
    int i;
    cout << "input an int:" << endl;
    if( cin >> i){
        cout << "yes, i=" << i << endl;
    }else{
        cout << "no, i=" << i << endl;
    }
    return 0;
}


$ g++ a3_io_state.cpp 

$ ./a.out 
input an int:
hi
no, i=0

$ ./a.out 
input an int:
21
yes, i=21
```





#### 查询流的状态

- 把流作为条件只能直到成功或失败，无法知道具体发生了什么。
- IO库定义了一个与机器无关的 iostate 类型，它提供了表达流状态的完整功能。
    * 该类型应该作为一个位集合来使用，使用方法同P137, 4.8 的 quizl 的方式一样。
    * IO库定义了4个 iostate 类型的 constexpr 值(P58, 2.4.4)，表示特定的位模式。
        * 这些值用来表示特定类型的IO条件，可以参与位运算符(P137, 4.8)一起使用来一次性检测或设置多个标志位。

- badbit 表示系统级错误，如不可恢复的读写错误。一旦被置位，流就无法再使用了。
- 发生可恢复错误后，failbit被置位，如期望读取数值却读出一个字符等错误。还可以修正，流还可以继续使用。
- 达到文件结尾，eofbit 和 failbit 都会被置位。
- goodbit 的值为0，表示流未发生错误。
- 如果 badbit, failbit 和 eofbit 任意一个被置位，则检测刘状态的条件会失败。


- 标准库定义了一组函数来查询这些标志位的状态：
    * good 在所有错误均未置位时返回true
    * 而 bad，fail 和 eof 则在对应错误位置置位时返回true
    * 此外，badbit被置位时，fail也会返回true。
    * 所以：good 或 fail 是确定流的总体状态的正确方法。
    * 实际上，将流当做条件使用的代码就等价于 `!fail()`。而eof和bad操作只能表示特定的错误。


例:

```
#include<iostream>
using namespace std;

//检查IO状态的条件: cin.fail()
int main(){
    int i;
    cout << "input an int:" << endl;
    cin >> i;

    if(!cin.fail())
        cout << "yes, i=" << i << endl;
    else
        cout << "no, i=" << i << endl;

    return 0;
}

$ g++ a4_check_IO_state.cpp 

$ ./a.out 
input an int:
3
yes, i=3

$ ./a.out 
input an int:
T
no, i=0
```



#### 管理条件状态

- 流对象的 rdstate 成员返回一个 iostate 值，对应流的当前状态。
- setstate 操作将给定条件位置位，表示发生了对应错误。
- clear 成员是一个重载的成员：他有一个不接受参数的版本，而另一个版本接受一个 iostate 类型的参数。
    * clear 不接受参数的版本清除（复位）所有错误标志位。执行 clear() 后，调用 good 会返回 true。

```
// 记住 cin 的当前状态
auto old_state = cin.rdstate(); //记住 cin 的当前状态
cin.clear();          //使cin有效
process_input(cin);    // 使用 cin
cin.setstate(old_state); //将cin置为原有状态
```


例: 

```
#include<iostream>
using namespace std;

int i=0;

void process_input(istream &is){
    cout << "input an int:" << endl;
    is >> i;
    cout << "i = " << i << endl;
}

void test(){
    // 记住 cin 的当前状态
    cout << "input a letter, to make an err state:" << endl;
    cin >> i;
    getchar();

    auto old_state = cin.rdstate(); //记住 cin 的当前状态
    cout << "1 cin.rdstate=" << cin.rdstate() << endl;
    
    cin.clear();          //使cin有效
    cout << "2 cin.rdstate=" << cin.rdstate() << endl;
    
    process_input(cin);    // 使用 cin
    cout << "3 cin.rdstate=" << cin.rdstate() << endl;
    
    cin.setstate(old_state); //将cin置为原有状态
    cout << "4 cin.rdstate=" << cin.rdstate() << endl;
}

int main(){
    test();
    return 0;
}


$ g++ a5_setstate.cpp 


$ ./a.out 
input a letter, to make an err state:
A
1 cin.rdstate=4
2 cin.rdstate=0
input an int:
200
i = 200
3 cin.rdstate=0
4 cin.rdstate=4


$ ./a.out 
input a letter, to make an err state:
A
1 cin.rdstate=4
2 cin.rdstate=0
input an int:
B
i = 0
3 cin.rdstate=4
4 cin.rdstate=4
```


- 带参数的 clear 版本接受一个 iostate 值，表示流的新状态。
- 为了复位单一的条件状态位，我们首先用 tdstate 读出当前条件状态，然后用位操作将所需位复位来生成新的状态。

```
//例: 将 failbit 和 badbit 复位，但保持 eofbit 不变。
cin.clear( cin.rdstate() & ~cin.failbit & ~cin.badbit);
```






### 8.1.3 管理输出缓冲

>P307/864













## 8.2 文件的输入输出































## 8.3 string 流































