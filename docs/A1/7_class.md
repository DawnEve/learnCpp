# 第七章 类

类的基本思想是 **数据抽象(data abstraction)** 和 **封装(encapsulation)**。

数据抽象是一种依赖于 **接口(interface)** 和 **实现(implementation)** 分离的编程(以及设计)技术。

- 类的接口包括用户所能执行的操作；
- 类的实现则包括类的数据成员、负责接口实现的函数体以及定义类所需要的各种私有函数。


- 封装实现了类的接口和实现的分离。封装后的类隐藏了它的实现细节，也就是说，类的用户只能使用接口而无法访问实现部分。
- 类要实现数据抽象和封装，首先要定义一个 **抽象数据类型(abstract data type)**.
    * 类的设计者负责考虑类的实现过程
    * 使用该类的程序员只需要抽象的思考类型做了什么，而无需了解类型的工作细节。









## 7.1 定义抽象数据类型

- Sales_item 类是一个抽象数据类型(P17, 1.5.1)。
- Sales_data 类不是一个抽象数据类型(P64, 2.6.1)。它允许用户直接访问它的数据成员。定义一些自己的操作，并隐藏它的数据成员，就变成抽象数据类型了。


### 7.1.1 设计 Sales_data 类

成员函数(member function).

自定义运算符(第14章, P490, 14.1)，这里先使用普通函数模拟。

- 执行加法和IO的函数不作为Sales_data的成员，而是定义为普通函数；
- 执行复合赋值运算的函数是成员函数。
- 无需专门定义赋值运算(原因在P239, 7.1.5)

综上，Sales_data 的接口应该包括如下操作：

- 一个 isbn 成员函数，用于返回对象的ISBN编号
- 一个combine成员函数，用于将一个 Sales_data 对象加到另一个对象上
- 一个名为 add 的函数，执行两个 Sales_data 对象的加法
- 一个 read 函数，将数据从 istream 读入到 Sales_data 对象中
- 一个 print 函数，将 Sales_data 对象的值输出到 ostream

> 关键概念：不同的编程角色。使用类的程序员也叫用户。

> 一个设计良好的类，既要直观且易于使用的接口，也必须具备高效的实现过程。


#### 使用改进的 Sales_data 类

如何使用以上接口的。




### 7.1.2 定义改进的 Sales_data 类

与P64, 2.6.1 定义的版本一致，包括：

- bookNo, string 类型，表示ISBN编号； 
- unites_sold， unsigned 类型，表示某本书的销量
- revenue, double 类型，表示这本书的总销售收入

该类包括的成员函数: 

- combine 
- isbn
- 计算平均价格的 avg_price，该函数目的并非通用，所以是类的实现的一部分，而非接口的一部分。


定义和声明成员函数的方法与普通函数差不多。 

- 成员函数的声明必须在类的内部，定义：类的内部、外部都可以。
- 作为接口组成部分的非成员函数，add, read, print, 定义和声明都在类的外部。

> 定义在类内部的函数是隐式的 inline 函数(P214, 6.5.2)

```
// Sales_data 类
struct Sales_data{
    //新成员：对于 Sales_data 对象的操作
    std::string isbn() const{ return bookNo;}
    Sales_data &combine(const Sales_data &);
    double avg_price() const; //最后的const 啥意思？
    // 数据成员和 P64 相同
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};

//Sales_data 的非成员接口函数
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
```



#### 定义成员函数

成员函数必须声明在类内部，但是其定义可以在类内或类外。

- isbn 函数定义在类内部了；
- combine 和 avg_price 定义在了类外；

> `std::string isbn() const{ return bookNo;}` 成员函数也是一个块，块内只有一个return语句，用于返回 Sales_data 对象的 bookNo 数据成员。

函数参数列表后的const？后面会讲。


#### 引入 this

调用成员函数时 `total.isbn()` 使用了点运算符(P133, 4.6)来访问total对象的isbn成员，并调用它。

当 isbn 返回 bookNo 时，实际上隐式的返回 total.bookNo。

成员函数通过一个名为this的额外的隐式参数来访问调用它的对象。调用一个成员函数时，用请求该函数的对象地址初始化this。

- 调用 total.isbn()，则编译器把total的地址传递给isbn的隐式形参 this，可以认为编译器将该调用重写成如下形式：

```
//伪代码，用于说明调用成员函数的实际执行过程
Sales_data::isbn(&total);
```

其中，调用 Sales_data 的isbn成员是传入了 total 的地址。

任何对类成员的直接访问都被看做this的隐式引用，也就是说，当isbn使用bookNo时，它隐式的使用了 this指向的成员，就像我们书写 this->bookNo 一样。

this 形参是隐式定义的。实际上，任何自定义名为 this 的参数或变量的行为都是非法的。我们可以在成员函数内部使用this，尽管没有必要。

```
std::string isbn() const{ return this->bookNo;}
```

因为 this 的目的总是指向“这个”对象，所以 this 是一个常量指针(P56, 2.4.2)，不允许改变this中保存的地址。

```
#include<iostream>
using namespace std;

//this 的目的是指向“这个”对象，所以是一个常量指针，不允许修改this中保存的值

class A{
    public:
    int i=10;
    A(int x){i = x;}
    int getI(){ return this->i; }
    int getI2(){ return i;} //this 不是必须的
    void modi(A a){
        cout << "this:" << this << endl;
        A *b=this;
        cout << a.i << endl;
        
        //this = &a; //this 不能作为左值
        //error: lvalue required as left operand of assignment
    }
};

int main(){
    A a1(1), a2(2);
    cout << a1.getI() << endl;
    cout << a1.getI2() << endl;

    a1.modi(a2);
    cout << "  a1:" << &a1 << endl;

    return 0;
}

$ g++ a1_this.cpp 
$ ./a.out 
1
1
this:0x7ffd11136470
2
  a1:0x7ffd11136470
```




#### 引入 const 成员函数

isbn 函数的另一个关键之处是紧随形参列表之后的const关键字，这里的const的作用是修改隐式this指针的类型。

- 默认，this指向的类类型是非常量版本的常量指针。例如，Sales_data成员函数中，this的类型是 `Sales_data *const`。
- 尽管 this 是隐式的，它仍然要遵循初始化规则，意味着（默认情况下）不能把this绑定到一个常量对象上(P56, 2.4.2)。
    * 这一情况就是说，我们不能在一个常量对象上调用普通的成员函数。


- 如果isbn是一个普通函数且this是一个普通的指针参数，则我们应该把this声明成 `const Sales_data *const`。
    * 毕竟，在函数体内不会改变this所指对象，所以把this设置为指向常量的指针有助于提高程序的灵活性(？我感觉是安全性)。


- 然而，this是隐式的且不会出现在参数列表中，在哪将this这个指针声明为const类型？
    * C++语言的做法是允许把this关键字放到成员函数的参数列表之后，此时，形参列表后的const表示this是一个指向常量的指针。

像这样使用const的成员函数，被称作**常量成员函数(const member function)**


可以把 isbn 的函数体想象成如下形式:

```
// 伪代码，说明隐式的this指针是如何使用的
// 下面的代码是非法的：因为我们不能显式的定义自己的this指针
// 谨记此处的this是一个指向常量的指针，因为isbn是一个常量成员
std::string Sales_data::isbn(const Sales_data *const this){
    return this->isbn;
}
```

因为this是指向常量的指针，所以常量成员函数不能改变调用它的对象的内容。isbn可以读取调用它的对象的数据成员，但是不能写入新值。

> 注意：常量对象，以及常量对象的引用或指针都只能调用常量成员函数。


> 函数名前后const关键字的区别?

```
// 补充一个网上的答案，仅供参考

const A *getPointer() 【const加在前】
表示此函数的return类型是const类型
如，const A *getPointer() 此函数的返回类型为"const A * "类型

A *getPointer() const【const写在后】
表示此函数是一个常函数，函数中只能作读取操作、不能作修改操作
```

例: 函数形参列表后的const表示该函数内的this是指向常量的，函数内只读，不能修改。

```
#include<iostream>
using namespace std;

// 函数参数列表后的const，要和不要有啥区别？

class A{
    public:
    int i=1;
    A(int x){ i =x;}

    void increase(int delta=1){ 
        //i+=delta; 
        this->i+=delta;
    }
    void increase2(int delta=1) const { 
        //i+=delta; //error: assignment of member ‘A::i’ in read-only object
        //this->i += delta; //error: assignment of member ‘A::i’ in read-only object

        A *this2=const_cast<A*>(this); //但是强制修改this的属性，把const去掉，就可以修改成员属性了
        // 说明函数花括号外的const确实是修饰函数内的this 的
        this2->i += delta;
    } 
    // 说明，const修饰的this，不能用于修改数据了

    int get(){ return i;}
    int get2() const { return i;} //加一个const有啥变换？
};

int main(){
    A a1(100);
    a1.increase(50);
    cout << a1.get() << endl; //A类型非常量，可以调用任何成员函数，const的和非const的
    cout << a1.get2() << endl;

    // diff? 
    A const a2(-20); //A类型常量 a2, a3, 只能调用const类型的成员函数
    const A a3(30);
    //a2.increase(); //error: passing ‘const A’ as ‘this’ argument discards qualifiers
    a2.increase2();
    //cout << a2.get() << endl; //error: passing ‘const A’ as ‘this’ argument discards qualifiers
    cout << a2.get2() << endl;

    //cout << a3.get() << endl; //error: passing ‘const A’ as ‘this’ argument discards qualifiers
    cout << a3.get2() << endl;

    return 0;
}

$ g++ a2_const_this.cpp 
$ ./a.out 
150
150
-19
30
```







#### 类作用域和成员函数

- 类本身就是一个作用域(P64, 2.6.1)
- 类的成员函数的定义嵌套在类的作用域之内，isbn用到的名字 bookNo 其实就是定义在 Sales_data 内的数据成员。
    * 即使 bookNo 定义在 isbn 之后， isbn 还是能够使用 bookNo。
    * 原因是，编译器分两步处理：扫描编译成员的声明，然后才是成员函数体（如果有）。
    * 结论：成员函数可以随意使用类中的其他成员，无须在意他们出现的次序。



#### 在类的外部定义成员函数

- 必须和类内的声明一致：返回类型、参数列表和函数名。
- 如果被声明为常量成员函数，那么定义时参数列表后明确指定const属性。
- 类外部定义的成员的名字必须包含它所属的类名
    * Sales_data::ave_price 使用了作用域运算符。它可以隐式地使用 Sales_data 的成员：

```
double Sales_data::avg_price() const {
    if(units_sold)
        return revenue / units_sold;
    else 
        return 0;
}
```


#### 定义一个返回this对象的函数

函数 combine 的设计初衷类似复合运算符 `+=` ，调用该函数的对象代表的是赋值运算符左侧的运算对象，右侧运算对象则通过显式的实参被传入函数。

```
Sales_data& Sales_data::combine(const Sales_data &rhs){
    units_sold += rhs.units_sold; //把rhs的成员加到this对象的成员上
    revenue += rhs.revenue;
    return *this; //返回调用该函数的对象
}
```

业务代码调用该函数 `total.combine(trans); //更新常量 total 当前的值`

- total 的地址被绑定到隐式的 this 参数上，而 rhs 绑定到 trans 上。因此当combine 执行下面的语句时：
    * `units_sold += rhs.units_sold; //把rhs的成员加到this对象的成员上`
    * 效果等同于 total.units_sold 和 trans.units_sold 的和，然后结果保存到 total.units_sold 中。
- 注意：该函数的返回类型和返回语句。一般，当我们定义的函数类似某内置运算符时，应该令该函数的行为尽量模仿这个运算符。
    * 内置赋值运算符把它的左测运算符当成左值返回(P129, 4.4)，
    * 为了与它一致，combine 函数必须返回引用类型(P202, 6.3.2)
    * 此时，左侧运算对象是一个 Sales_data，所以返回类型就应该是 Sales_data&。
- 我们无需使用this指针访问调用者的某个具体成员，而是需要把调用函数的对象当做一个整体来访问： 
    * `return *this; //返回调用该函数的对象`
    * 其中， return 语句解引用this指针，获得执行该函数的对象，换句话说，上面这个调用返回total的引用。


例1: 探索 新建对象和内部this的指针。

```
#include<iostream>
using namespace std;

// 打印函数内外的this地址
class A{
    public:
    void getAddr(){
        cout << "in :" << this << endl;
    }
};

int main(){
    A a1;
    cout << "out:" << &a1 << endl;
    a1.getAddr();
    return 0;
}

$ g++ a3_add_in_out_class.cpp 
wangjl@YStation:~/data/project/learnCpp/A1/7$ ./a.out 
out:0x7ffdc0d66a17
in :0x7ffdc0d66a17
```


例2: （复习）返回引用的函数作为左值

```
#include<iostream>
using namespace std;

//返回引用的函数作为左值

//返回大的值的引用
int &bigger(int &i1, int &i2){
    return i1>i2? i1: i2;
}

int main(){
    int a1=1, a2=20;
    // 函数作为左值
    bigger(a1, a2) = 5000; //把大的值修改为5000

    cout << "a1=" << a1 << endl;
    cout << "a2=" << a2 << endl;

    return 0;
}

$ g++ a4_return_ref_as_lvalue.cpp 
$ ./a.out 
a1=1
a2=5000
```



例3: 测试`return *this;`的左值写入效果 //todo 不太懂

```
#include<iostream>
using namespace std;

//返回引用的函数作为左值

class A{
    int number;
    public:
    A(int x){number=x;}
    int getN() const { return number;}

    A &bigger(A &rhs){ //也可传入指针
        return number > rhs.getN()? *this: rhs;    
    }
};

int main(){
    A a1(1), a2(20);
    // 函数作为左值，因为函数返回的是引用
    a1.bigger(a2) = 5000; //把大的值修改为5000。等号左侧是一个对类的引用，怎么赋值的？
    a1=10; //这又是什么语法？？？竟然可以赋值成功

    cout << "a1=" << a1.getN() << endl;
    cout << "a2=" << a2.getN() << endl;
    
    return 0;
}

$ g++ a4_return_ref_as_lvalue2.cpp 
$ ./a.out 
a1=10
a2=5000
```

例4：测试 `return *this;` 的链式调用效果

```
#include<iostream>
using namespace std;

//返回引用的函数作为左值

class A{
    int number;
    public:
    A(int x){number=x;}
    int getN() const { return number;}

    A &combine(A &rhs){
        number += rhs.getN();
        return *this;
    }
};

int main(){
    A a1(1), a2(20), a3(100);
    // 函数作为左值，因为函数返回的是引用
    a1.combine(a2).combine(a3); //可以链式调用下去

    cout << "a1=" << a1.getN() << endl;
    cout << "a2=" << a2.getN() << endl;
    cout << "a3=" << a3.getN() << endl;
    
    return 0;
}

$ g++ a4_return_ref_as_lvalue3.cpp 
$ ./a.out 
a1=121
a2=20
a3=100
```









### 7.1.3 定义类相关的非成员函数

- 类作者通常需要定义一些辅助函数，比如 add, read 和 print 等。
- 这些属于类的接口的组成部分，但是并不属于类本身。


和一般函数一样，通常声明和定义分离开来(P168, 6.1.2)。

- 如果函数概念上属于类但不定义在类中，则一般应与类声明（而非定义）在同一个头文件内。
- 这样，用户使用接口的任何部分都只需要引入一个头文件。

> 注意：一般来说，如果非成员函数是类接口的组成部分，则这些函数的声明应该与类在同一个头文件中。


#### 定义 read 和 print 函数

代码与之前的类似: P66, 2.6.2

```
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
```

- read 函数从给定流中读到给定的对象中，print函数则负责把给定对象中的信息打印到给定的流中。
- 还有两点需要注意：
    * read和print分别接受一个IO类型的引用作为其参数，这是因为IO类属于不能被拷贝的类型，只能通过引用传递。读写都要改变流的内容，所以不能是对常量的引用。
    * print函数不负责换行。一般把格式控制交给用户。

```
#include<iostream>
using namespace std;

struct Sales_data{
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;

    std::string isbn() const { return bookNo;} //必须加const：print函数的形参要求
    double avg_price() const;
};
double Sales_data::avg_price() const {
    if(units_sold)
        return revenue / units_sold;
    else 
        return 0;
}

//接口成员，但不是类成员
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

int main(){
    Sales_data sd1, sd2;
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd1); //输入
    print(cout, sd1) << endl; //输出
    print(cout, sd2) << endl; //输出
    return 0;
}

$ g++ a5_read_print.cpp 
$ ./a.out 
Please input info for sd1: bookNo units_sold price
Book12 4 20.5
Book12 4 82 20.5
 0 0 0
```



#### 定义 add 函数

把两个 Sales_data 对象相加。

```
Sales_data add(const Sales_data &lhs, const Sales_data &rhs){
    Sales_data sum = lhs; //把lhs 的数据成员拷贝给sum
    sum.combine(rhs); //把rhs的数据成员加到sum当中
    return sum;
}
```

拷贝类的对象，其实是拷贝类的对象的数据成员。









### 7.1.4 构造函数 constructor

- 无论何时，只要类的对象被创建，就会执行构造函数。
- 更多构造函数：P257, P551, P689, 第13章。


- 构造函数的名字和类名相同，构造函数没有返回值。其他与普通函数类似。
- 不同的构造函数必须在参数类型和参数数量上有区别。
- 构造函数不能被声明成 const 的(P231, 7.1.2)。
    * 我们创建类的一个const 对象时，直到构造函数完成初始化，对象才能真正取得其“常量”属性。
    * 因此，构造函数在 const 对象的构造过程中可以向其写值。



#### 合成的默认构造函数

- 没有为对象提供初始值，则执行默认初始化(P40, 2.2.1)。
- 类通过一个特殊的构造函数来控制默认初始化过程，该函数叫做 **默认构造函数 default constructor**，无须任何实参。

- 默认构造函数的特殊性：如果没有显式的定义构造函数，则编译器就会隐式的声明一个默认构造函数。
- 编译器创建的构造函数又称为 **合成的默认构造函数**。合成规则：
    * 如果存在类内初始值(P64, 2.6.1)，用它来初始化
    * 否则，默认初始化(P40, 2.2.1)该成员



#### 某些类不能依赖于合成的默认构造函数

合成默认构造函数只适合非常简单的类。

对于一个普通类，必须定义它自己的默认构造函数，原因：

1. 编译器只有发现不包含任何构造函数的情况下，才生成默认的构造函数；
    * 如果一个类在某些情况下需要控制对象初始化，那么该类很可能在所有情况下都需要控制。
2. 对于某些类，合成构造函数可能执行错误的操作。
    * 包含内置类型或符合类型成员的类，应该在累的内部初始化这些成员。
3. 编译器不能为某些类合成默认的构造函数。
    * 类中包含其他类类型的成员，且该成员的类型没有默认构造函数。
    * 其他无法生成正确的默认构造函数的情况(P449, 13.1.6)

```
$ cat a6_must_define_default_constructor.cpp
#include<iostream>
using namespace std;

//必须自定义 默认构造函数的3个原因

// 1.只有不包含任何构造函数的类，编译器才会合成默认构造函数
class A{
public:
    A(int x){ cout << x << endl; }
};

// 2.默认初始化的值是不确定的
class B{
public:
    void get(){
        cout << x << " " << y << endl;
    }
private:
    int x;
    int y=25;
};

// 3. 编译器不能为某些类合成构造函数
class Book{
    public:
    Book(int x){}
};
class C{
    A a;
};

int main(){
    //A a1; //error: no matching function for call to ‘A::A()’

    B b2;
    b2.get(); //1815907360 25

    C c;

    return 0;
}
```





#### 定义 Sales_data 的构造函数

将定义4个：

- 一个 istream&，从中读取一条交易信息
- 一个 const string&，表示ISBN编号；一个 unsigned，表示售出的图书数量；以及一个double，表示图书的售出价格。
- 一个 const string&，表示ISBN编号；编译器将赋予其他成员默认值。
- 一个空参数列表（即默认构造函数），有其他构造函数，则必须定义一个默认构造函数。

```
struct Sales_data{
    //构造函数
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s){}
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(std::istream &);
    //... 其他不变
}
```


#### = default 的含义

`Sales_data() = default;` 是C++11新标准，生成 合成默认构造函数。

- 其中 =default 既可以和声明一起出现在类内部，也可以作为定义出现在类的外部。
- 在类内部，则默认构造函数是内联的；外部，默认不是内联的。


```
#include<iostream>
using namespace std;

// = default; 表示默认构造函数
class A{
    int i=10;
    int j=5;
public:
    A(int x){ i=x;} //初始化 方法1
    A(int x, int y): i(x), j(y){} //初始化 方法2
    A() = default; //有其他构造函数，就必须有默认构造函数
    void info(){
        cout << "i=" << i << ", j=" << j << endl;
    }
};

int main(){
    A a1, a2(-6), a3(-1,1);
    a1.info();
    a2.info();
    a3.info();

    return 0;
}

$ g++ a7_constructor_equal_default.cpp 
$ ./a.out 
i=10, j=5
i=-6, j=5
i=-1, j=1
```


#### 构造函数初始值列表

这两个构造函数，注意到参数列表后花括号前，出现了 冒号及冒号后的代码。

```
Sales_data(const std::string &s): bookNo(s){}
Sales_data(const std::string &s, unsigned n, double p):
    bookNo(s), units_sold(n), revenue(p*n) {}
```

- 花括号定义了（空的）函数体；
- 新出现的冒号及冒号后的部分，叫做 **构造函数初始值列表**
    * 负责为新创建的对象的一个或几个数据成员赋初始值。
    * 格式是成员名字列表，后面跟着圆括号括起来的（或者花括号内的）成员初始值。
    * 不同成员的初始化通过逗号分开


- 第一个构造函数，只有一个参数，则没有明确值的成员变量，则按照合成默认构造函数相同的方式隐式初始化。
    * 本例中使用类内初始值初始化。
    * 等价于 `Sales_data(const std::string &s): bookNo(s), unites_sold(0), revenue(0){}`

> 最佳实践：构造函数不应轻易覆盖掉类内的初始化值，除非新赋的值与原值不同。

> 注意:上面2个构造函数的函数体都是空的。这是因为构造函数的唯一目的就是为数据成员赋初始值，一旦没有其他任务，则函数体就是空的。


```
#include<iostream>
using namespace std;

// 构造函数：初始值列表
class Time{
    string name="";
    int time[3];
public:
    //参数列表后、函数体前：冒号以及冒号后的，类成员用逗号分割，括号(或花括号)内是形参。
    Time(int h, int m, int s): time{h, m, s}{} 
    Time(int h, int m, int s, const string &clockName): time{h, m, s}, name(clockName){}
    void now(){
        cout << "clockName:" << name << ",\ttime: ";
        for(auto i : time)
            cout << i << ":";
        cout << endl;
    }
};

int main(){
    Time t1(5,10,3);
    t1.now();

    Time t2(5,10,3, "getUp");
    t2.now();

    return 0;
}

$ g++ a8_constructor_init.cpp 
$ ./a.out 
clockName:,     time: 5:10:3:
clockName:getUp,        time: 5:10:3:
```





#### 在类的外部定义构造函数

以 istream 为参数的构造函数:

```
//类外的构造函数，定义
Sales_data::Sales_data(std::istream &is){
    read(is, *this); //read函数的作用：从is中读取一条交易信息，存入this对象中
}
```
- 构造函数没有返回类型。必须有类的命名空间 `className::className`, 又因为该函数与类名同名，所以是一个构造函数。
- 该函数没有构造函数初始值列表，或者说它的构造函数初始值列表是空的（参数列表后、函数体之前是空的）。
- 没有出现在构造函数初始值列表中的成员，通过类内初始值（如果存在的话）完成初始化，或者执行默认初始化。


- 特别注意 read 的第二个参数是一个 Sales_data 对象的引用。
- P232, 7.1.2 提到：使用this来把对象当成一个整体访问，而非直接访问对象的某个成员。
    * 本例中，*this 将 this 对象作为实参传递给 read 函数。

```
#include<iostream>
using namespace std;

//类外定义构造函数：一个依赖输入的构造函数
class A{
    int i;
public:
    A()=default;
    A(istream &); //构造函数，声明
    void show(){
        cout << "i=" << i << endl;
    }
};

//构造函数，定义
A::A(istream &is){
    cout << "Please input the init value of i in class A: " << endl;
    is >> i;
}

int main(){
    A a1(cin);
    a1.show();

    return 0;
}

$ g++ a9_constructor_outside.cpp 
$ ./a.out 
Please input the init value of i in class A: 
18
i=18
```










### 7.1.5 拷贝、赋值和析构

- 对象在几种情况下会拷贝：初始化变量，及以值的方式传递或返回一个对象时。(P187, P200)
- 使用赋值运算符，发生赋值操作。(P129)
- 对象不再存在时，执行销毁操作，
    * 局部对象，创建它的块结束时被销毁
    * 当 vector 对象(或数组) 销毁时，存储在其中的对象也会被销毁。

不主动定义，则编译器会替我们合成。

赋值语句: `total = trans; //处理下一本数的信息`

其行为与下面的代码相同:

```
//Sales_data 的默认赋值操作等价于
total.bookNo = trans.bookNo;
total.units_sold = trans.units_sold;
total.revenue = trans.revenue;
```

赋值的自定义方式见  第13章。



#### 某些类不能依赖于合成的版本

当类需要分配类对象之外的资源时，合成的版本经常失效。

- 第12章分配和管理动态内存；
- 13.1.4, P447: 管理动态内存的类通常不能依赖于上述合成版本。


- 很多需要动态内存的类能（而且应该）使用vector对象或者string对象管理必要的存储空间。
- 使用vector 或 string 的类能避免分配和释放内存带来的复杂性。


例: 当前版本的书店类

```
#include<iostream>
using namespace std;

// Sales_data 类 v1
struct Sales_data{

    //构造函数
    Sales_data() = default;
    Sales_data(const std::string &s): bookNo(s){}
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) {}
    Sales_data(std::istream &);

    //新成员：对于 Sales_data 对象的操作
    std::string isbn() const { return bookNo;}
    Sales_data &combine(const Sales_data &);

    double avg_price() const; //最后的const 啥意思？
    // 数据成员和 P64 相同
    std::string bookNo;
    unsigned units_sold=0;
    double revenue=0.0;
};

//Sales_data 的非成员接口函数 声明放前面
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

/******************* 函数(构造函数)的定义 ********************/

//类外的构造函数，定义
Sales_data::Sales_data(std::istream &is){
    read(is, *this); //read函数的作用：从is中读取一条交易信息，存入this对象中
}

// 非成员函数的定义
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

// 接口函数，但不是类成员

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

Sales_data add(const Sales_data &lhs, const Sales_data &rhs){
    Sales_data sum = lhs; //把lhs 的数据成员拷贝给sum
    sum.combine(rhs); //把rhs的数据成员加到sum当中
    return sum;
}


/**
 * @brief 测试每一个构造函数
 * 
 * @return int 
 */

int main(){
    Sales_data sd1, sd2;
    // 测试IO
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd1); //输入
    cout << "Please input info for sd1: bookNo units_sold price" << endl;
    read(cin, sd2); //输入
    print(cout, sd1) << endl; //输出
    print(cout, sd2) << endl; //输出

    // 合并
    sd1.combine(sd2);
    print(cout, sd1) << endl; //输出
    
    return 0;
}

$ g++ a0_0_struct.cpp 

$ ./a.out 
Please input info for sd1: bookNo units_sold price
A1 10 20.5
Please input info for sd1: bookNo units_sold price
A1 2 30.5
A1 10 205 20.5
A1 2 61 30.5
A1 12 266 22.1667
```
















## 7.2 访问控制与封装

访问说明符 access specifiers 加强类的封装性：

- public 后的整个程序内可被访问，public 定义的类的接口；
    * 构造函数和部分成员函数(接口)
- private 后的成员只能被本类访问，不能被使用该类的代码访问。private 部分封装了类的实现细节。
    * 数据成员，作为实现的部分函数。

一个类可以包含0个或多个访问说明符，而且对某个访问说明符出现的次数也没有严格限定。

访问说明符的范围，到下一个访问说明符或者类定义结束为止。



#### 使用 class 或 struct 关键字


> class 或 struct 的唯一区别，是默认访问权限。 class 默认 private，struct 默认 public。




### 7.2.1 友元

- 既然 Sales_data 的数据成员是 private 的，非类成员函数(read/print/add)无法访问。
- 解决方法，是让这些类或者函数变成类的友元(friend).
    * 形式是：friend 关键字开头，在类中再添加一次函数声明；


- 友元声明只能出现在类内部，但类内位置不限。推荐在类开始或结束位置集中声明友元。
- 友元不是类成员，不受访问控制符的约束。


```
class Sales_data{
// 为 Sales_data 的非成员函数所做的友元声明
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);
// ... 其他同上
}
```

例:

```
#include<iostream>
using namespace std;

// 友元：能访问类私有成员的函数
class A{
private: //对友元没影响
    friend void add(A &, int); //添加友元声明，就可以访问私有成员i了
    int i=0;
public:
    void show(){
        cout << i << endl;
    }
};

void add(A &a, int x){
    a.i += x;  //只有友元函数、类内成员函数才可以访问私有成员
}

int main(){
    A a1;
    add(a1, 25);
    a1.show();

    return 0;
}

$ g++ a10_friend.cpp 
$ ./a.out
25
```


> 关键概念：封装的益处

- 确保用户代码不会无意间破坏封装对象的状态
- 被封装的类的具体实现细节可以随时改变，而无需调整用户级别的代码。
    * private 数据成员，好处是方便排错，把修改限定在有限的几个操作中。
    * 尽管当类的定义改变时无需更改用户代码，但是使用了该类的源文件必须重新编译。



#### 友元的声明

- 友元函数要声明两次：一次在类内带friend前缀，获取访问权限；一次正常函数声明。
- 正常函数声明一般和类声明放到一个头文件中。

> Note: 许多编译器并未强制限定友元函数必须在使用之前在类的外部声明。不过，最好先声明再使用，像普通函数一样。













## 7.3 类的其他特性

介绍上文没有体现出来的C++关于类的语法要点: 类型成员、类的成员的类内初始值、可变数据成员、内联成员函数、从成员函数返回*this、如何定义并使用类类型及友元类等。


### 7.3.1 类成员再探

定义2个相互关联的类：Screen 和 Window_mgr.

#### 定义一个类型成员

- Screen 表示一个窗口。包括一个string 成员，3个string::size_type 类型的成员，分别表示screen内容、光标位置、屏幕高和宽。
- 类内除了定义数据、函数成员外，还可以定义某种类型在类内的别名。类内别名也受访问限制，可以是public或private中的一种:

```
class A{
public:
    typedef std::string::size_type pos;
private:
    pos cursor = 0;
    pos height =0, width = 0;
    std::string contents;
};
```

注意两点：
- 和前面一致，类别名可以使用 typedef 或 using 声明；
- 用来定义类型的成员必须先定义后使用，这一点和普通类成员不同。因此类型成员一般定义在类开始的地方。

```
    //typedef std::string::size_type pos; //类别名
    using pos = std::string::size_type; //等价声明，同上
```


#### Screen 类的成员函数

添加构造函数：用户定义屏幕尺寸和内容；移动光标；读取给定位置的字符。

```
class Screen{
public:
    //类型别名，也受访问控制： public or private
    //typedef std::string::size_type pos; //类别名
    using pos = std::string::size_type; //等价声明，同上

    // 构造函数
    Screen() = default; //有其他构造函数，就必须定义默认构造函数
    Screen(pos h, pos w, char c): height(h), width(w), contents( h * w, c){}

    // 成员函数
    char get() const { //读取光标处的字符，隐式内联
        return contents[cursor]; 
    }
    inline char get(pos h, pos w) const ; //显式内联
    Screen &move(pos r, pos c); //能在之后设置为内联

private:
    pos cursor = 0;
    pos height =0, width = 0;
    std::string contents;
};
```

- 有其他构造函数，就必须自定义默认构造函数(P237, 7.1.4)
- 第二个构造函数，隐式的使用了cursor 类内初始值。

```
// 回顾字符串内的初始化
string test(5, 'c');
cout << test << endl; //ccccc
```


#### 令成员作为内联函数

- 规模较小的函数，适合设置为内联的。
- 类内定义的成员函数是自动 inline 的(P213, 6.5.2)
    * 因此 Screen 的 构造函数和返回光标所指字符的 get 函数默认是 inline 的。
- 类内能用 inline 关键字显式声明内联成员函数，也可以在类外部用inline 修饰函数的定义。

```
inline                               //在函数的定义处指定 inline
Screen& Screen::move(pos r, pos c){
    pos row = r * width;
    cursor = row + c; //位置 = 行*宽度 + 列
    return *this; //以左值的形式返回对象
}

char Screen::get(pos r, pos c) const {  //在类内部声明为 inline
    pos row = r * width; //计算 位置
    return contents[row + c]; //返回给定列的字符
}
```

我们无须在声明和定义处同时说明 inline ，虽然这么做是合法的。

最好只在类外部定义的地方说明 inline，方便理解。

> note: inline 成员函数应该与相应的类的定义在同一个头文件中。(在头文件中定义 inline 函数的原因见 P214, 6.5.2)





#### 重载成员函数

同一般函数的重载。

测试刚才定义的2个get函数。

```
    Screen screen(10, 20, 'z');
    char ch=screen.get(); //调用 Screen::get();
    cout << ch << endl;

    ch = screen.get(0,2); //调用 Sceen::get(pos, pos)
    cout << ch << endl;
```



#### 可变数据成员 mutable

- 我们想修改类的某个数据成员，即使在一个 const 成员函数内。
    * 方法：在变量声明中添加 mutable 关键字。
- 一个 **可变数据成员(mutable data member)** 永远不会是 const，即使它是 const 对象的成员。
    * 因此，一个 const 成员函数，可以修改一个可变成员的值。

例: 给 Screen 类添加一个可变成员 access_ctr，通过它最终每个Screen 成员被调用的次数:

```
#include<iostream>
using namespace std;

//可变成员，甚至可以被const函数修改
class Screen{
public:
    void some_member() const;
    void show(){ cout << access_ctr << endl;}
    void show2(){ cout << access_ctr2 << endl;}
private:
    mutable size_t access_ctr=0; //即使一个const 对象内也能被修改
    size_t access_ctr2=0; //没有 mutable 前缀
};

void Screen::some_member() const{
    ++access_ctr; //保存一个计数器，用于记录函数被调用次数
    //++access_ctr2; //error: increment of member ‘Screen::access_ctr2’ in read-only object
}

int main(){
    Screen sc1;
    sc1.some_member();
    sc1.some_member();
    sc1.show();
    sc1.show2();

    return 0;
}

$ g++ b2_mutable.cpp 
$ ./a.out 
2
0
```

尽管 some_member 是一个 const 成员函数，它任然可以修改 access_ctr 的值。这就是可变成员。




#### 类数据成员的初始值

C++11标准中，最好的默认值是声明一个类内初始值。

```
class Window_mgr{
private:
    // 这个 Window_mgr 追踪的 Screen
    // 默认情况下，一个 Window_mgr 包含一个标准尺寸的空白 Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};
```

> 提供一个类内初始化值时，必须以为符号=或者花括号形式表示。





### 7.3.2 返回 *this 的成员函数

添加函数，设置光标所在位置的字符、或任一给定位置的字符。

```
class Screen{
public:
    Screen &set(cahar);
    Screen &set(pos, pos, cahar);
    // 其他不变
};

inline Screen &Screen::set(char c){
    contents[cursor]=c; // 设置当前光标所在位置的新值
    return *this; //将this对象作为左值返回
}
inline Screen &Screen::set(pos r, pos c, char c){
    contents[r*width + c]=c; // 设置当前光标所在位置的新值
    return *this; //将this对象作为左值返回
}
```

- 和move 操作一样，我们的set成员的返回值是调用set 的对象的引用(P232, 7.1.2)
- 返回引用的函数是左值(P202, 6.3.2)，意味着返回的是对象本身而非副本。
    * 可以做链式调用: `myScreen.move(4,0).set('#');`，等价于 `myScreen.move(4,0);  myScreen.set('#');`

如果令move和set返回Screen 而非 Screen&，则上述语句的行为将大不相同:

```
// 如果 move 返回Screen而非 Screen&
Screen temp=myScreen.move(4, 0); //对返回值进行拷贝
temp.set('#'); //不会改变 myScreen的contents
```

- 加入我们当初定义的返回类型不是引用，则move返回值将是*this的副本(P201, 6.3.2);
    * 因此调用set只能改变临时副本，而不能改变myScreen的值。


```
#include<iostream>
using namespace std;

//返回*this

class A{
private:
    int i=0;
public:
    A()=default;
    A(int x): i(x){}
    A set(int x){ i = x; return *this;} //函数返回类型是本身，则发生复制
    A &cset(int x){i = x; return *this;} //函数返回类型是引用，则返回的是本身，无复制
    void show() const { cout << i << endl;}
};


int main(){
    A a1(1), a2(2);
    cout << "&a1:" << &a1 << ", &a2=" << &a2 << endl;
    A b1=a1.set(10);
    A &b2=a2.cset(20);
    const A &b3=a2.cset(300);
    a1.show();
    a2.show();
    b3.show();
    //可见，cset 返回的是引用，其地址和a2一样
    cout << "&b1:" << &b1 << ", &b2=" << &b2 <<", &b3=" << &b3 << endl;

    return 0;
}


$ g++ b3_return_star_this.cpp 
$ ./a.out 
&a1:0x7ffe390e5cdc, &a2=0x7ffe390e5ce0
10
300
300
&b1:0x7ffe390e5ce4, &b2=0x7ffe390e5ce0, &b3=0x7ffe390e5ce0
```



#### 从 const 成员函数返回 *this

- 添加一个 display 函数，负责打印 Screen 的内容。我们希望这个函数能和 move 和 set 链式调用，所以也要返回对执行它的对象的引用。
- 打印不需要修改值，所以令display 为一个const成员，此时 this指向const的指针而*this是const对象。
    * 由此推断，display的返回类型是 const Screen&。
    * 如果真的令 display 返回一个const引用，则我们将无法后续链式调用。

```
Screen myScreen;
//如果display返回常量引用，则调用set将引发错误
myScreen.display().set('*');
```
即使 myScreen 是个非常量对象，对set的调用也无法通过编译。

问题在于 display 返回的是const版本的常量引用，我们无权set一个常量对象。


> Note: 一个const成员如果以引用的形式返回*this，那么它的返回类型将是常量引用。


例: 链式调用版的 display() 函数

```
类内声明:
    Screen &display(ostream&);

类外定义:
inline Screen &Screen::display(ostream &os){
    os << this->contents << endl;
    return *this; //将this对象作为左值返回
}

main中调用:
Screen screen(4, 5, 'z');
screen.display(cout).move(3,0).set('#').display(cout);
```



#### 基于 const 的重载

- 因为非常量版本的函数对常量是不可用的，所以只能在一个常量对象上调用const成员函数。
- 可以在非常量对象上调用常量、非常量版本，但是此时非常量版本是最佳匹配。

例: 定义 do_display 私有函数，负责打印 Screen 的实际工作。 所有的 display 将调用该函数，返回返回执行操作的对象。

```
class Screen{
public:
    //根据对象是否const重载display函数
    Screen &display(std::ostream &os){
        cout << "version: non-const" << endl;
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const {
        cout << "version: const" << endl;
        do_display(os);
        return *this;
    }
private:
    //负责打印Screen 的内容
    void do_display(std::ostream &os) const{
        os << contents;
    }
    //其他不变
};
```

在某个对象上调用display时，该对象是否const 决定了应该调用display 的哪个版本:

```
// 非常量版本:
Screen screen(4, 5, 'z');
screen.display(cout).move(3,0).set('#').display(cout);

// 常量版本:
const Screen blank(5,3, ' ');
blank.display(cout); //调用常量版本
```

> 建议：对于公共代码使用私有功能函数。

为什么费力气单独定义一个私有的 do_display 函数?

- 一个基本的愿望是：避免多出使用同样的代码。
- 预期随着类的发展，display函数会更加复杂，此时把相同的操作写到一处而不是两处更好管理
- 我们可能在开发过程中给 do_display() 函数添加调试信息，而正式版会去掉。这样只有一处添加或删除更容易控制。
- 这个额外的函数不会增加任何运行时开销，类内定义，隐式内联的。






### 7.3.3 类类型

即使2个类的成员完全相同，它们也是2个不同的类型。

```
class A{};
class B{};
A a1;
B b1=a1; //错误: a1和b1的类型不同
//error: conversion from ‘A’ to non-scalar type . requested
```

声明类类型时，class关键字可有可无:

```
Sales_data item1; //默认初始化 Sales_data 类型的对象
class Sales_data item1; //等价，同上。从C继承来的
```


#### 类的声明

不定义类，只声明:

```
class Screen;  //Screen 类的声明
```

这种声明叫前向声明(forwar declaration)。

对于类类型，声明后、定义前是一个

















































## 7.4 类的作用域



































## 7.5 构造函数再探



































## 7.6 类的静态成员



































