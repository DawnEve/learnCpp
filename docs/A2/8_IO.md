# 8. IO 库

已经介绍过的

- istream(输入流)类型，提供输入操作
- ostream(输出流)类型，提供输出操作
- cin，一个 istream 对象，从标准输入读取数据
- cout，一个 ostream 对象，向标准输出写入数据
- cerr，一个 ostrem 对象，向标准输出写入数据
- `>>` 运算符，用来从一个 istream 对象读取输入数据
- `<<` 运算符，用来向一个 ostream 对象写入输出数据
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

- 每个输出流都管理一个缓冲区，用来保存程序读写的数据: ` os << "please enter a value:";`
- 导致缓冲刷新(即：数据真正写到输出设备或文件)的原因有很多：
    * 程序正常结束，作为 main 函数的 return 操作的一部分，缓冲刷新被执行
    * 缓冲区满，需要刷新后才能继续写入缓冲区
    * 使用操作符，比如 endl 来显式刷新缓冲区
    * 在每个输出操作之后，我们可以采用操纵符 unitbuf 设置流的内部状态，来清空缓冲区。
        * 默认情况下，对cerr是设置 unitbuf 的，因此写到cerr的内容都是立即刷新的。
    * 一个输出流可能被关联到另一个流。当读写被关联的流时，关联到的流的缓冲区会被刷新。
        * 如，默认情况下，cin和cerr都关联到cout，因此，读cin或写cerr会导致cout的缓冲区被刷新。


#### 刷新输出缓冲区

- 除了 endl外，还有 flush 和 ends两个。
    * flush 刷新缓冲区，但不输出任何额外的字符
    * ends 向缓冲区插入一个空字符，然后刷新缓冲区

```
#include<iostream>
using namespace std;

//刷新输出缓冲区
int main(){
    int flag=0;
    cout << "1 hi!" << endl; //输出hi和一个换行，然后刷新缓冲区
    cout << "2 hi!" << flush; //输出hi，然后刷新缓冲区，不附加任何额外的字符
    if(flag)
        cout << "|" << endl;

    cout << "3 hi!" << ends; //输出hi和一个空字符，然后刷新缓冲区
    if(flag)
        cout << "|" << endl;
}

$ g++ a6_flush.cpp 

$ ./a.out 
1 hi!
2 hi!3 hi!wangjl@YStatio
```



#### unitbuf 操纵符

- 使用 unitbuf 操纵符，可以在每次输出操作后刷新缓冲区。
    * 它告诉流在接下来的每次操作之后都进行一次 flush 操作。
- 而 nounitbuf 操纵符则重置流，恢复正常的系统管理的缓冲区刷新机制

```
cout << unitbuf; //此后的所有输出操作都会立即刷新缓冲区
// 任何输出都立即刷新，无缓冲
cout << nounitbuf; //回到正常的缓冲方式
```

> 警告：如果程序崩溃，输出缓冲区不会被刷新。

也就是可能执行了，但是在缓冲区内，来不及输出。





#### 关联输入和输出流

当一个输入流被关联到输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流。

标准库将 cout 和 cin 关联在一起。 `cin >> ival;` 导致 cout 的缓冲区被刷新。

> note: 交互式系统通常应该关联输入流和输出流。这意味着所有输出，包括用户提示信息，都会在读操作之前被打印出来。

- tie 有两个重载的版本(P206, 6.4):
    * 不带参数的，返回指向输出流的指针：如果本对象关联到一个输出流，则返回的就是指向这个流的指针；未关联，则返回空指针。
    * 接受一个指向 ostream 的指针，将自己关联到另一个 ostream: `x.tie(&o);` 将流x关联到输出流o。
- 既可以把一个 istream 对象关联到另一个 ostream，也可以将一个 ostream 关联到另一个 ostream:
- 每个流同时最多关联到一个流，但多个流可以同时关联到同一个 ostream。


```
cin.tie(&cout); //仅仅使用从来展示：标准库将cin和cout关联在一起

//old_tie 指向当前关联到cin的流（如果有的话）
ostream *old_tie = cin.tie(nullptr); //cin 不再与其他流关联

//将cin与cerr关联：这不是一个好主意，因为cin应该与cout关联
cin.tie(&cerr); //读取cin会刷新cerr而不是cout
cin.tie(old_tie);  //重建 cin 和 cout 间的正常访问
```


例: 没看到关联与否的区别 //todo

```
#include<iostream>
using namespace std;

//关联输入流和输出流：保证在读之前，输出所有用户提示

int main(){
    cin.tie(&cout); //仅仅使用从来展示：标准库将cin和cout关联在一起

    //old_tie 指向当前关联到cin的流（如果有的话）
    ostream *old_tie = cin.tie(nullptr); //cin 不再与其他流关联

    //test
    //cerr << "some error:";
    cout << "input an int:";
    int i;
    cin >> i;

    //将cin与cerr关联：这不是一个好主意，因为cin应该与cout关联
    cin.tie(&cerr); //读取cin会刷新cerr而不是cout
    cin.tie(old_tie);  //重建 cin 和 cout 间的正常访问

    return 0;
}

$ g++ a7_tie.cpp 
$ ./a.out 
input an int:100
```













## 8.2 文件的输入输出

- 头文件 fstream 定义了三个类型支持文件IO
    * ifstream 从一个给定文件读取数据
    * ofstream 向一个给定文件写入数据
    * fstream 读写给定文件。P676 17.5.3 对同一个文件流既读又写。
- 与之前cin和cout操作一样：
    * 使用IO运算符 (`<<` `>>`) 读写文件
    * getline从一个 ifstream 读取一行数据。


- 表 8.3 fstream 特有的操作
    * fstream fstrm; 创建一个未绑定的文件流。fstream是头文件 fstream 中定义的一个类型
    * fstream fstrm(s); 创建一个 fstream，并打开名为s的文件。s可以是 string 类型，或者一个指向c风格字符串的指针。这些构造函数都是 explicit 的。默认的文件模式 mode 依赖于 fstream 的类型。
    * fstream(s, mode); 与前一个构造函数类似，但按照指定mode打开文件
    * fstrm.open(s)  打开名为 s 的文件，并将文件与 fstrm 关联。s是string或指向c风格字符串的指针。默认文件mode依赖于fstream的类型。返回void。
    * fstrm.close() 关闭 fstrm 绑定的文件。返回 void
    * fstrm.is_open() 返回一个bool值，指出与 fstrm 关联的文件是否成功打开且未关闭。





### 8.2.1 使用文件流对象


- 想读写一个文件时，先定义一个文件流对象，并将对象和文件关联起来。
    * 每个文件流都定义了一个 open 方法，它完成相关操作，定位给定的文件，并视情况打开为读或写模式。
    * 创建文件流对象时，可以提供文件名（可选）。如果提供文件名，open 会自动调用。

```
ifstream in(ifile);  //构造一个 ifstream 并打开给定文件
ofstream out;   // 输出文件流未关联到任何文件
```

在C++11中，文件名既可以是string对象，也可以是C风格字符数组(P109, 3.5.4)。旧版本标准库只允许C风格字符数组。



#### 用 fstream 代替 iostream&

- 使用基类型对象的地方，也可以使用继承该类型的对象来替代。
    * 意味着，接受一个 iostream 类型引用（指针）参数的函数，也可以接受 fstream(或 sstream) 类型来调用。
    * 也就是说，如果一个函数接受一个 ostream& 参数，我们调用这个函数时，可以传递给他一个 ofstream 对象。
    * 对 istream& 和 ifstream 也是类似。


> 报错: `error: variable ‘std::ifstream input’ has initializer but incomplete type` 的解决方法，是引入 `#include <fstream>`.


例1: main() 函数传递参数，打开文件，读取内容，处理后保存到文件。

使用 7.1.3 节中 read 和 print 函数读写命名函数。

```
    ifstream input(argv[1]); //打开输入文件
    ofstream output(argv[2]); //打开输出文件
    Sales_data total;
    if( read(input, total) ){
        Sales_data trans; //保存下一条记录
        while( read(input, trans)){
            if(total.isbn() == trans.isbn()){
                total.combine(trans);
            }else{
                print( output, total) << endl; //打印结果
                total = trans; //处理下一本
            }
        }
        print(output, total) << endl; //打印最后一本书的销售额
    }else 
        cerr << "No data?!" << endl;
```


再次强调：记得引入 `#include <fstream>` 头文件。

- 该函数与 P229 写法几乎完全相同。
- 重要的是对 read 和 print 的调用。虽然2函数定义时的形参分别是 istream& 和 ostream&，但是可传递实参 fstream 对象。

完整代码如下:

```
#include<iostream>
#include <fstream> 
using namespace std;

class Sales_data{
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
public:
    Sales_data() = default;
    Sales_data(std::istream &);
    std::string isbn() const { return bookNo;}
    Sales_data &combine(const Sales_data &);
private:
    double avg_price() const;
    string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};

/********** 声明部分 ************/
std::istream &read(std::istream&, Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);


/********** 定义部分 ************/
// 类外的构造函数，定义
Sales_data::Sales_data(std::istream &is){
    read(is, *this); //read函数的作用：从is中读取一条交易信息，存入this对象中
}

// 输入的交易信息：ISBN、售出总数和售出价格
istream &read(istream &is, Sales_data &item){
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

ostream &print(ostream &os, const Sales_data &item){
    os << item.isbn() << " " << item.units_sold << " "
       << item.revenue << " " << item.avg_price();
    return os;
}


// 成员函数的定义
double Sales_data::avg_price() const {
    if(units_sold)
        return revenue / units_sold;
    else 
        return 0;
}

Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold; //把rhs的成员加到this对象的成员上
    revenue += rhs.revenue;
    return *this; //返回调用该函数的对象
}



// 读文件
int main(int argc, char *argv[]){
     Sales_data sd1, sd2;
    /*
    // 测试IO
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd1); //输入

    print(cout, sd1) << endl; //输出
    */

    ifstream input(argv[1]); //打开输入文件
    ofstream output(argv[2]); //打开输出文件
    Sales_data total;
    if( read(input, total) ){
        Sales_data trans; //保存下一条记录
        while( read(input, trans)){
            if(total.isbn() == trans.isbn()){
                total.combine(trans);
            }else{
                print( output, total) << endl; //打印结果
                total = trans; //处理下一本
            }
        }
        print(output, total) << endl; //打印最后一本书的销售额
    }else 
        cerr << "No data?!" << endl;
    return 0;
}

/*
$ cat a8_out.txt
S1 4 80.4 20.1
S2 1 30.5 30.5

$ g++ a8_read_file.cpp
$ ./a.out a8_file.txt a8_out.txt

$ cat a8_out.txt 
S1 4 80.4 20.1
S2 1 30.5 30.5
*/
```

例2: 仅读文件。见 `learnCpp/A2/8/a8_read_file2.cpp`

例3: 仅写文件。见 `learnCpp/A2/8/a9_write_file.cpp`






#### 成员函数 open 和 close

先定义一个空文件流对象，随后调用 open 将它与文件关联起来。

```
ifstream in(ifile);   //构筑一个 ifstream 并打开给定文件
ofstream out; // 输出文件流未与任何文件相关联
out.open(ifile + ".copy"); 打开指定文件
```

- 如果调用 open 失败，failbit 会被置位(P280, 8.1.2)
- 因为调用open 可能失败，进行 open 成功与否的检测通常是一个好习惯。

```
if(out) //检查 open 是否成功
        // open 成功，我们可以使用该文件了
```

与之前的 cin 用作条件相似，如果open 失败，条件为假，我们就不会去使用 out 了。

- 一旦一个文件流已经调用 open，它就保持了对应文件的关联。再调用open会失败，并会导致 failbit 被置位。随后试图使用文件流的操作都会失败。
- 为了将文件流关联到另一个文件，必须首先关闭已经关联的文件。一旦成功关闭，才可以打开新的文件：

```
in.close(); //关闭文件
in.open(ifile + "2"); //打开另一个文件
```

如果 open 成功，则open会设置流的状态，时得 good() 为 true。



例: 一个流读取2个文件。要先读取一个，关闭后再读取另一个。

```
#include<iostream>
#include<fstream>
using namespace std;

//读取另一个文件前，要关闭文件。

int main(int argc, char *argv[]){
    string str;
    cout << "input a line: stop with ctrl+D" << endl;
    
    // 从键盘输入
    /*while(getline(cin, str)){
        cout << ">" << str << endl;
    }*/

    // 从2个文件输入
    //ifstream input(argv[1]);
    ifstream input;
    cout << "argc="<< argc << endl;
    for(int i=1; i<argc; i++){
        input.open(argv[i]);
        if(!input){
            cout << "Error: input "<< argv[1] << " open failed!" << endl;
            return 1;
        }

        while(getline(input, str)){
            cout << i << ">" << str << endl;
        }
        //使用完关闭
        input.close();
    }

    return 0;
}

/*
$ g++ a10_open_close_open.cpp 
$ ./a.out a8_file.txt a8_file2.txt 
input a line: stop with ctrl+D
1>S1 4 20.1
1>S2 1 30.5
2>S1 40
2>S2 10
*/
```








#### 自动构造与析构

例: 从main传入一系列文件名，每个都要处理。

- 每个循环创建一个名为 input 的 ifstream 对象，并打开来读取给定文件。
- 用if检查 open 是否成功。成功则处理文件，失败则给出错误信息，并处理下一个文件。
- 因为 input 是 for 循环的局部变量，它的每个循环步骤都要创建和销毁一次(P165, 5.4.1)。
    * 当 fstream 对象离开其作用域时，与之关联的文件会自动关闭。下一步循环中， input 会再次创建。

> Note: 当一个 fstream 对象被销毁时，close 会自动被调用。

```
#include<iostream>
#include<fstream>
using namespace std;

// main 函数接受一个要处理的文件列表(P196, 6.2.5)
int main(int argc, char *argv[]){
    //对每个传递来的文件执行循环
    int i=0;
    for(auto p=argv +1; p!=argv + argc; ++p){
        i++; //文件编号
        ifstream input(*p); //创建输出流并打开文件
        if(input) {   //如果文件打开成功，“处理”该文件
            // process file
            string str;
            while(getline(input, str)){
                cout << i << ": " << str << endl;
            }
        }else{
            cerr << "Open file failed: " + string(*p);
        }
    } //每个循环步骤 input 都会离开作用域，因此会被销毁
}

/*
$ g++ a11_auto_close.cpp 
$ ./a.out a8_file.txt a8_file2.txt
1: S1 4 20.1
1: S2 1 30.5
2: S1 40
2: S2 10
*/
```


测试： for 循环(while也一样)内变量是局部变量，每一轮都要创建和销毁一次。

```
#include<iostream>
using namespace std;

class Book{
public:
    int i;
    Book(int x=0): i(x){
        cout << "Book()" << endl;
    }
    ~Book(){
        cout << "~Book()" << endl;
    }
};

int main(){
    Book *book = new Book(200);
    cout << book->i << endl;
    delete book;
    // in while
    int x=3;
    for(int i=0; i<x; i++){
        Book book(i);
        cout << book.i << endl;
    }

    return 0;
}


$ g++ a12_variable_in_while.cpp 
$ ./a.out 
Book()
200
~Book()
Book()
0
~Book()
Book()
1
~Book()
Book()
2
~Book()
```







### 8.2.2 文件模式

每个流都有一个关联的 **文件模式**(file mode)，用来指出如何使用文件。

- 图 8.4 文件模式
    - in 以读方式打开
    - out 以写方式打开
    - app 每次写操作前均定位到文件末尾
    - ate 打开文件后立即定位到文件末尾
    - trunc 截断文件
    - binary 以二进制方式进行IO

- 无论哪种方式打开文件，都可以指定文件模式，调用open打开文件时可以，用一个文件名初始化流隐式打开文件时也可以。
- 指定文件模式有如下限制
    * 只可以对 ofstream 或 fstream 对象设定 out 模式
    * 只可以对 ifstream 或 fstream 对象设定 in 模式
    * 只有当 out 也被设定时才可设定 trunc 模式
    * 只有 trunc 没被设定，就可以设定 app 模式。在 app 模式下，即使没有显式指定 out 模式，文件也总是以输出方式被打开。
    * 默认情况下，即使我们没有指定 trunc ，以 out 模式打开的文件也会被截断。为了保留以 out 模式打开的文件的内容，我们必须同时设定 app 模式，这样只会将数据追加到文件末尾； 或者同时指定 in 模式，即打开文件同时进行读写操作(P676, 17.5.3)。
    * ate 和 binary 模式可用于任何类型的文件流对象，且可以与其他任何文件模式组合使用。


每个文件流都有默认的文件模式：

- ifstream 默认以 in 模式打开
- ofstream 默认以 out 模式打开
- fstream 默认以 in 和 out 模式打开








#### 以 out 模式打开文件会丢失已有数据

默认打开一个 ofstream 时，文件内容会被丢弃。阻止清空文件的方法是同时指定 app 模式。

```
    // 这几条，file 都被截断
    //ofstream out(fileName); //隐含以输出模式打开文件并截断文件
    //ofstream out(fileName, ofstream::out); //隐含的截断文件
    //fstream out(fileName, ofstream::out  | ofstream::trunc);

    //为了保留原文件内容，必须显式指定 app 模式
    //ofstream out(fileName, ofstream::app); //隐含的输出文件
    ofstream out(fileName, ofstream::out | ofstream::app);
```

> 警告: 保留被 ofstream 打开的文件中已有数据的唯一方法是显式指定 app 或 in 模式。


例: 打开文件，如果不指定 app 模式，则默认丢失文件原来的内容。

```
#include<iostream>
#include<fstream>
using namespace std;

// ofsteam 默认使用 out 模式打开文件。指定 app 模式才能保留源文件内容

int main(){
    string s2 = "hello, Tom 01 02 03 04!";
    string fileName="a13.txt";

    // 这几条，file 都被截断
    //ofstream out(fileName); //隐含以输出模式打开文件并截断文件
    //ofstream out(fileName, ofstream::out); //隐含的截断文件
    //fstream out(fileName, ofstream::out  | ofstream::trunc);

    //为了保留原文件内容，必须显式指定 app 模式
    //ofstream out(fileName, ofstream::app); //隐含的输出文件
    ofstream out(fileName, ofstream::out | ofstream::app);

    out << s2 << endl;
    out.close();

    cout << "Please view file: $ cat " << fileName << endl; 

    return 0;
}

$ g++ a13_ofstream_out.cpp                            
$ ./a.out                  
Please view file: $ cat a13.txt

$ cat a13.txt
hello, Tom 01 02 03!
hello, Tom 01 02 03 04!
```







#### 每次调用 open 时都会确定文件模式

对于一个给定的流，每当打开文件时，都可以改变其文件模式。

```
    ofstream out; // 未指定文件打开模式
    out.open("a14.txt"); //模式隐含设置为输出和截断
    out.close(); //关闭out(原文件已经清空了)。以便我们用于其他文件。

    out.open("a13.txt", ofstream::app); //模式为输出和追加
    out << "hi, Tom" << endl;
    out.close();
```

- 通常情况下，默认打开文件是 out 模式，意味着同时使用 trunc 模式，因此该文件被清空。
- 当open时明确指定 app 模式时，文件得以保留，写在文件末尾。

> Note: 每次打开文件时，都要设置文件模式，可能是显示地设置，也可能是隐式的设置。当程序未指定时，就是用默认值。




















## 8.3 string 流

- sstream 头文件定义了三个来支持内存IO，这些类型可以向string 写数据。
- 从 string 读取数据，就像 string 是一个 IO 流一样。
    * istringstream 从 string 读取数据
    * ostringstream 向 string 写数据
    * stringstream 可以读写 string
    * 需要头文件 sstream

- 表 8.5 stringstream 特有的操作
    * sstream strm; # strm 是一个未绑定的 stringstream 对象。sstream是头文件 sstream 中定义的一个类型
    * sstream strm(s); #strm是一个sstream对象，保存 string s的一个拷贝。此构造函数是 explicit 的(P265, 7.5.4)
    * strm.str(); 返回 strm 所保存的 string 的拷贝
    * strm.str(s); 将 string s 拷贝到 strm 中。返回void


### 8.3.1 使用 istringstream 

- 某项工作是对整行文本，而其他工作是处理行内的单个单词时，可以使用 istringstream

例: 假定有一个文件，列出一些人和他们的电话号码。

``
morgan 111 112
drew 211
lee 311 312 333 314
``

- 每条记录都是人名开头
- 一个人有1个或多个号码。

定义一个类来描述输入数据:

```
struct PersonInfo{
    string name;
    vector<string> phone;
};
```

- 读取文件，并创建一个 PersonInfo 类型的 vector。
- 每个 vector 中的元素对应文件的一行记录。
- 每个循环读取一行

```
    string line, word;  //分别保存输入的一行和单词（电话号码）
    vector<PersonInfo> people;  //保存来自输入的所有记录
    // 逐行读入数据，直到 cin 遇到文件末尾(或其他错误)
    while(getline(cin, line)){
        PersonInfo info;  //创建一个结构体对象
        istringstream record(line); //将记录绑定到刚读入的行
        record >> info.name; //记录名字
        while( record >> word){ //读取电话号码
            info.phones.push_back( word ); // 将电话追加到 号码向量
        }
        people.push_back(info); //将一行记录追加到 people 末尾
    }
```

完整例子:
```
#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
using namespace std;

// stringstream 示例
// 注意: 要加头文件 #include<sstream>

struct PersonInfo{
    string name;
    vector<string> phones;

    void show(){
        cout << "> " << name << ":";
        for(auto i : phones){
            cout << i << " / ";
        }
        cout << endl;
    }
};

int main(){
    //打开文件
    ifstream fin("a15.txt");

    // 从文本文件读取
    string line, word;  //分别保存输入的一行和单词（电话号码）
    vector<PersonInfo> people;  //保存来自输入的所有记录
    // 逐行读入数据，直到 cin 遇到文件末尾(或其他错误)
    while(getline(fin, line)){
        PersonInfo info;  //创建一个结构体对象
        istringstream record(line); //将记录绑定到刚读入的行
        record >> info.name; //记录名字
        while( record >> word){ //读取电话号码: 从字符流读取
            info.phones.push_back( word ); // 将电话追加到 号码向量
        }
        people.push_back(info); //将一行记录追加到 people 末尾
    }

    // 关闭文件
    fin.close();

    // 输出
    for(auto i : people){
        i.show();
    }
}

$ g++ a15_stringstream.cpp 
$ ./a.out 
> morgan:111 / 112 / 
> drew:211 / 
> lee:311 / 312 / 333 / 314 /
```




### 8.3.2 使用 ostringstream 

- 逐步构建输出，希望最后一期打印时， ostringstream 就很有用。

例: 上节的例子，如果想逐个验证电话号码并改变其格式。有效的输出到新文件，无效的舍弃并打印无效信息详情。

- 输出前先写入到一个内存 ostringstream 中。

```
    for(const auto &entry: people){ //遍历people中的每一项
        ostringstream formatted, badNums; //每个循环步骤创建的对象
        for(const auto &nums: entry.phones){ //对每个数
            if(!valid(nums)){
                badNums << " " << nums; //将数的字符串形式存入 badNums
            }else{
                // 将格式化的字符串"写入"formatted
                formatted << " " << format(nums);
            }
        }

        // 一条有一个错误的，这一条就不输出到文件了
        if(badNums.str().empty()) { //没有错误的数字
            os << entry.name << " " 
               << formatted.str() << endl; //打印名字和格式化的数
        }else{
            cerr << "input error: " << entry.name 
                 << " invalid number(s) " << badNums.str() << endl;
        }
    }
```

- 以上程序，假设已经定义2个函数 valid 和 format，分别负责号码验证和格式化的功能。
- 注意的是对字节流 formatted 和 badNums 的使用，可以直接使用 输出运算符 `<<`  向这些 字符流对象 写入数据。
    * 实际这些 写入 操作转换为对 string 的操作，分别向 formatted 和 badNums 中的string 对象添加字符。







## 小结

- C++标准库处理面向流的输入和输出:
    * iostream 处理控制台IO
    * fstream 处理命名文件IO
    * stringstream 完成内存 string 的IO
- IO 对象有一组条件状态，可以检测和设置
- 文件模式







> 2022.8.29 end;