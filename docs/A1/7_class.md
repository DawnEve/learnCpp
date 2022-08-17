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

对于类类型，声明后、定义前是一个 **不完全类型(incomplete type)**: 是一个类类型，但是不清楚包含哪些成员。


不完全类型只能用于以下情景：

- 定义指向这种类型的指针或引用；
- 声明（不能定义）以不完全类型作为参数或者返回类型的函数。


P268， 7.6 描述一种例外情况：直到类被定义之后，数据成员才能被声明成这种类型。

- 完成类的定义，然后编译器才能知道数据成员需要多少空间。
- 因为只有类全部完成后类才算被定义，所以一个类的成员类型不能是该类自己。
    * 但是可以是指向自身类型的引用或指针。

```
class Link_screen{
    Screen window;
    Link_screen *next;
    Link_screen *prev;
};
```


例: 定义2个类，X包含一个指向Y的指针，Y包含一个类型为X的对象

```
//不完全声明后，可以定义引用或指针
class X;
class Y;

class X{
    public:
    Y *py;
    int i=1;
};

class Y{
    public:
    X x;
    int j=20;
    X &get(){
        return this->x;
    }
};
```






### 7.3.4 友元再探

- 之前把3个普通函数定义为友元；
- 类也可以把其他的类定义为友元。
    * 也可以把其他类(已经定义过的)的成员函数定义为友元。
- 友元函数还能定义在类的内部，是隐式内联的。


#### 类之间的友元关系

例：Window_mgr类的某些成员要访问它管理的 Screen 类的内部数据。Window_mgr::clear 函数负责把一个指定Screen 的内容设定为空白。

- Window_mgr::clear 需要能访问 Screen 的私有数据成员；
- 实现方法，就是 Screen 类把 Window_mgr 指定为它的友元

```
class Screen{
    //Window_mgr的成员可以访问Screen 类的私有成员
    friend class Window_mgr;
    //Screen 类的其余部分
};
```


如果一个类指定了友元类，则友元类的成员函数可以访问此类包括私有成员在内的所有成员。

```
class Window_mgr{
public:
    //窗口中每个屏幕的编号
    using ScreenIndex = std::vector<Screen>::size_type;
    //按照编号将指定的Screen重置为空白
    void clear(ScreenIndex);
private:
    // 这个 Window_mgr 追踪的 Screen
    // 默认情况下，一个 Window_mgr 包含一个标准尺寸的空白 Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};


void Window_mgr::clear(ScreenIndex i){
    //s是一个 Screen 的引用，指向我们想清空的那个屏幕
    Screen &s= screens[i];
    //将那个Screen 设置为空白
    s.contents = string(s.height * s.width, ' ');
}
```

- 解释:
    * 首先定义s为screens vector 中第i个位置上的Screen 的引用
    * 然后利用该Screen 的宽高计算出新的string 对象，令其含有若干空白字符。
    * 最后，把空白字符赋值给该Screen对象的 contents 成员。
- 如果 clear 不是 Screen 的友元，上面代码编译失败，因为clear将不能访问Screen的私有成员: height, width, contents。
- 注意：友元没有传递性。如果 Window_mgr有它自己的友元，则这些友元并不会理所当然的具有访问 Screen 的特权。

> Note: 每个类负责控制自己的友元类或友元函数。


例1: 友元类可以访问其宿主类(?)的私有成员。

```
#include<iostream>
using namespace std;

//A是B的友元类，则A能访问B的私有成员
class A;
class B;
class C;

class B{
    //声明B类的友元类：包括A
    friend class A;
public:
    void show(){ cout << "A.x=" << x << endl; }
private:
    int x=2;
};

class C{
public:
    void show(){ cout << "C.x=" << x << endl; }
private:
    int x=3;
};

class A{
public:
    void showB(B &b){ 
        b.show(); 
        cout << b.x << endl; //B和C的唯一区别，就是B的友元包括A，所以可以在A中访问B的私有成员。
    }
    void showC(C &c){ 
        c.show(); 
        //cout << c.x << endl; //error: ‘int C::x is private within this context
    }
};

int main(){
    A a;
    B b;
    C c;
    a.showB(b);
    a.showC(c);

    return 0;
}

$ g++ b6_friend_class.cpp 
$ ./a.out 
A.x=2
2
C.x=3
```

例2: 友元不具有传递性。

```
#include<iostream>
using namespace std;

//A是B的友元，B是C的友元，则A不能访问C的私有成员。
class A;
class B;

class C{
    friend class B; //B是C的友元类，B能访问C的私有成员
    int x=3;
};

class B{
    friend class A; //A是B的友元类, A能访问B的私有成员
    int x=2;
public:
    void showC(C &c){
        cout << c.x << endl; //在B中访问C的私有成员
    }
};

class A{
    int x=1;
public:
    void showB(B &b){
        cout << b.x << endl; //在A中访问B的私有成员
    }
    void showC(C &c){
        //cout << c.x << endl; //在A中 不能 访问C的私有成员
        // error: ‘int C::x is private within this context
    }
};

int main(){
    A a;
    B b;
    C c;
    b.showC(c);

    a.showB(b);
    //a.showC(c);

    return 0;
}

$ g++ b7_friend_no_pass.cpp 
$ ./a.out 
3
2
```





#### 令成员函数作为友元

更细的粒度。

例: Screen 仅为 Window_mgr::clear 提供访问权限。

当把一个成员函数声明声明为友元时，必须明确该函数属于哪个类。

```
class Screen{
    // Window_mgr::clear 必须在 Screen 类之前声明
    friend void Window_mgr::clear(ScreenIndex);
    //Screen 类的其余部分
};
```

声明类的成员函数为友元，需要特别注意程序结构，以满足声明、定义的彼此依赖关系。

- 首先定义 Window_mgr 类，其中声明 clear 函数，但是不能定义它。
    * 在 clear 使用 Screen 的成员之前必须声明 Screen
- 然后定义Screen类，包括对于clear的友元声明
- 最后定义clear，此时它才可以使用Screen的成员。

例: 

```
#include<iostream>
#include<vector>
using namespace std;

//声明 Window_mgr::clear函数 为 Screen 类的友元，需要注意程序结构
//1. 声明Screen类。定义 Window_mgr 类，声明clear函数(不能定义，因为还没有Screen类)
class Screen;

class Window_mgr{
public:
    void clear(int x);
    Window_mgr& push(Screen);

    Screen &get(int i){
        return screens[i];
    }
private:
    vector<Screen> screens;
};

//2. 定义Screen类，包括对clear的友元声明
class Screen{
    friend void Window_mgr::clear(int);
public:
    Screen(char ch){
        contents = string(10, ch);
    }
    void print(string s=""){ cout << s << contents << endl;}
private:
    string contents; //(10, '*');
};

//3. 最后定义Window_mgr::clear函数
void Window_mgr::clear(int x){
    Screen &s = screens[x];
    s.contents="";
}

Window_mgr& Window_mgr::push(Screen s1){
    screens.push_back(s1);
    return *this;
}

int main(){
    Window_mgr win_mgr;
    Screen scr1('#'), scr2('+');
    win_mgr.push(scr1).push(scr2);
    //查看
    win_mgr.get(0).print("1:");
    win_mgr.get(1).print("2:");

    //获取第0个
    Screen &cscr1 = win_mgr.get(0);
    cscr1.print("b 1:");
    //清空 下标是0的内容
    win_mgr.clear(0);
    cscr1.print("a 1:");

    //再次查看
    win_mgr.get(0).print("1:");
    win_mgr.get(1).print("2:");

    return 0;
}

$ g++ b8_friend_use_fn_in_class.cpp 
$ ./a.out 
1:##########
2:++++++++++
b 1:##########
a 1:
1:
2:++++++++++
```



#### 函数重载与友元

如果一个类想把一组重载函数都声明为它的友元，必须一一声明。

```
// 重载 storeOn 函数
extern std::ostream& storOn(std::ostream &, Screen &);
extern BitMap& storeOn(BitMap &, Screen &);
class Screen{
    // storeOn 的 ostream 版本能访问 Screen 对象的私有成员
    friend std::ostream & storeOn(std::ostream &, Screen &);
    // ... Screen 函数其余部分
};
```

上述声明，接收 BitMap&作为参数的版本不能访问 Screen 的私有成员。



#### 友元声明与作用域

- 类和非成员函数的声明不是必须在它们的友元声明前。一个名字第一次出现在一个友元声明中时，我们隐式的假定该名字在当前作用域是可见的。然而，友元本身不一定声明在当前作用域中(P241, 7.2.1)。
- 即使在类内定义该函数，也要在类的外部提供声明从而使函数可见。
    * 即使仅仅用声明友元的类的成员调用该友元函数，该函数也必须是被声明过的。
    * 友元声明不能代替函数声明，它们是相互独立的。

```
#include<iostream>
using namespace std;

//友元声明不能代替函数声明，它们是相互独立的

class X{
public:
    friend void f(){ cout << "f()" << endl; }; //友元函数可以定义在类内部
    //X(){ f(); } //错误：f还没有被声明
    // error: ‘f was not declared in this scope
    void g();
    void h();
};

//void X::g(){ return f();} //错误: f还没有被声明
//error: ‘f was not declared in this scope

void f(); //函数声明
void X::h(){ return f();} //正确: 现在f的声明在作用域中可见了

int main(){
    X x;
    x.h();
}

$ g++ b9_friend_decl_must.cpp 
$ ./a.out 
f()
```

> 友元的声明仅仅是可见性，而函数声明则是必须的，是影响作用域内是否可见的。











## 7.4 类的作用域

- 每个类都会定义它自己的作用域。
- 类的作用域外，普通成员只能由对象、引用或者指针使用成员访问运算符来访问。
- 对于类类型成员使用作用域运算符访问。

```
Screen::pos ht=24, wd=80; //使用 Screen 定义的pos类型
Screen scr(ht, wd, ' ');
Screen *p = &scr;
char c= scr.get(); //访问scr对象的get成员
c= p->get();       //访问p所指对象的get成员
```


#### 作用域和定义在类外部的成员

- 类是一个作用域，所以类外访问必须提供类名和成员名字。
- 一旦遇到类名，则其余部分就是类的作用域之内了，这里剩余部分包括参数列表、函数体。

例: Window_mgr 类的clear成员(P251, 7.3.4)，该函数的参数用到了 Window_mgr 类定义的一种类型。

不必再说明 ScreenIndex 是 Window_mgr 类定义的。编译器也知道 screens 也是 Window_mgr 类定义的。

```
void Window_mgr::clear(ScreenIndex i){
    Screen &s = screens[i];
    s.contents = string(s.height * s.width, ' ');
}
```

函数的返回值通常在函数名之前。因此定义在外部的类成员函数，返回类型中使用的名字都位于类的作用域之外。

例: 添加 Window_mgr::addScreen 函数，负责向显示器添加一个新的屏幕，返回类型是 ScreenIndex，用户可以通过它定位到指定的Screen。

```
Class Window_mgr{
public:
    //向窗口添加一个 Screen ，返回它的编号
    ScreenIndex addScreen(const Screen &);
    //其他成员不变
};

//处理返回类型，之后我们才进入 Window_mgr 的作用域
Window_mgr::ScreenIndex 
Window_mgr::addScreen(const Screen &s){
    screens.push_back(s);
    return screens.size()-1;
}
```

返回类型出现在类名之前，事实上位于 Window_mgr 类的作用域之外。必须指定类名作用域。

```
#include<iostream>
using namespace std;

//返回类内定义的类型别名，作用域范围处理
class A{
public:
    using pos = int;
    pos &get();
private:
    pos x=8;
};

A::pos &A::get(){
    return x;
}

int main(){
    A a;
    cout << a.get() << endl;
    return 0;
}

$ g++ b10_typedef_in_class_return.cpp 
$ ./a.out 
8
```








### 7.4.1 名字查找与类的作用域

名字查找(name lookup)寻找与所用名字最匹配的声明的过程：

- 名字所在块中寻找其声明语句，只考虑在名字的使用前出现的声明；
- 如果没找到，继续查找外层作用域
- 如果最终没有找到匹配的声明，则程序报错。

定义在类内部的成员函数，解析过程有所区别：

- 首先，编译成员的声明
- 直到类全部可见后才编译函数体。

> Note: 编译器处理完类的全部声明后才会处理成员函数的定义。

- 按照2阶段处理模式，成员函数直到整个类可见后才被处理，所以它能使用类中定义的任何名字。
- 如果成员声明和函数的定义是同时处理的，则我们将不得不在成员函数中只使用已经出现的名字。




#### 用于类成员声明的名字查找

- 两阶段处理只适用于成员函数内使用的名字。
- 声明中使用的名字，包括返回类型或者参数列表中使用的名字，都必须在使用前确保可见。
    * 如果某个成员的声明中出现了尚未出现的名字，则编译器将会在定义该类的作用域中继续查找。

```
typedef double Money;
string bal;
class Account {
public:
    Money balance(){ return bal; }
private:
    Money bal;
}
```

当编译器看到 balance函数声明语句时，它将在 Account 类的范围内寻找 Money 的声明。编译器只考虑 Account 中在使用 Money 前出现的声明，因为没找到，所以到 Account 的外层作用域中查找。

- 本例中，编译器会找到 Money 的 typedef 语句，该类型被用作 balance 函数的返回类型和数据成员bal的类型。
- balance 函数体在整个类可见后才被处理，因此该函数 return 语句返回名为 bal 的成员，而非外层作用域的 string 对象。


例:

```
#include<iostream>
using namespace std;

//用于类成员声明的名字查找
typedef double Money;
string bal="outside";

class Account {
public:
    Money balance(){ return bal; }
private:
    Money bal=3.14;
};

int main(){
    Account act;
    cout << act.balance() << endl;

    return 0;
}

$ g++ b11_delc_of_method_lookup.cpp 
$ ./a.out 
3.14
```

注意：返回值 bal 是哪一个？虽然它出现的早，但是类内名字扫描完才处理函数体，所以类内定义的同名 bal 隐藏了类外定义的 bal，函数返回的是类内定义的 bal。




#### 类型名要特殊处理

一般，内层作用用可以重新定义外层作用域中出现过的名字，即使该名字在内层作用域中使用过(??)

例1: 内层重新定义外层出现过、内层使用过的名字。

```
#include<iostream>
using namespace std;

//
string food="rice";

int main(){
    food += " is good";
    cout << food << endl;

    string food = "corn"; //重新定义外层定义、内层使用过的名字
    cout << food << endl;
    return 0;
}

$ g++ b12_redefine_name_used_from_out.cpp 
$ ./a.out 
rice is good
corn
```


- 但是，在类中，如果成员使用了外层的某个名字，且该名字代表一种类型，则类内不能在之后重新定义该名字。

```
#include<iostream>
using namespace std;

typedef double Money;
class Account{
public:
    Money balance(){ return bal; } //使用外层作用域的 Money，且Money表示类型
    //typedef double Money; //错误: 不能重新定义 Money
    //error: declaration of ‘typedef double Account::Money’ changes meaning of ‘Money’
private:
    Money bal=10;
};

int main(){
    Account act;
    cout << act.balance() << endl;

    return 0;
}

$ g++ b13_typedef_no_re_in_class.cpp 
$ ./a.out 
10
```

注意：即使 Account 类内定义的 Money 类型与外部作用域一致，上述代码依旧报错。（有些编译器忽略）

> Tip: 类型名的定义通常出现在类的开始，这样确保所有使用该类型的成员都出现在类型名的定义之后。




#### 成员定义中的普通块作用域的名字查找

成员函数中使用的名字按照如下方式解析:

- 首先是成员函数内查找。函数使用前出现的声明才被考虑；
- 成员函数内没有，则找类内查找，类内所有成员都考虑，不管声明的先后；
- 类内没有该名字的声明，则在成员函数定义之前的作用域内继续查找。

一般，不建议使用其他成员的名字作为某个成员函数的参数。为了演示，本例违反了这一约定:

```
// 注意：这段代码只是为了说明，不符合最佳实践：不建议为参数和成员使用同样的名字

int height; //定义一个名字，稍后将在 Screen 中使用
class Screen{
public:
    typedef std::string::size_type pos;
    void dummy_fcn(pos height){
        cursor = width * height;  //哪个 height？是哪个参数？
    }
private:
    pos cursor=0;
    pos height=0, width=0;
};
```


例:

```
#include<iostream>
using namespace std;

// 函数中变量的查找顺序
/*
dummy_fcn 的 height 是哪个？
1.函数内，使用前：是形式参数
2. 如果想使用成员变量，则可以使用 this->height 或 Screen::height
*/

int height; //定义一个名字，稍后将在 Screen 中使用
class Screen{
public:
    typedef std::string::size_type pos;
    void dummy_fcn(pos height){
        //cursor = width * height;  //哪个 height？是传入的参数

        //不好的写法，成员函数中的名字不应该隐藏同名的类成员
        //cursor = width * this->height; //height是类的私有成员
        cursor = width * Screen::height; //height是类的私有成员
    }
    void show(){ cout << cursor << endl;}
private:
    pos cursor=0;
    pos height=1, width=1;
};

int main(){
    Screen scr1;
    scr1.dummy_fcn(50);
    scr1.show();
    return 0;
}

$ g++ b14_var_in_class_method.cpp 
$ ./a.out 
1
```

> Note: 尽管类成员被隐藏了，但我们仍然能通过加上类的名字作用域或者使用this指针强制访问成员。

最好的确保使用成员height的方法是给参数起个其他名字，防止隐藏类成员：

```
    void Screen::dummy_fcn(pos ht){
        cursor = width * height; //成员变量 height
    }
```

- 编译器在成员函数内找不到，就在类内全局查找，然后找到了。
    * 类两次扫描，先扫描所有的名字声明，然后类完全可见时再扫描函数体。




#### 类作用域之后、在外围的作用域中查找

如果函数和类内都没找到，则接着在外围的作用域中查找。

如果想要外层作用域中的、被类成员隐藏的变量怎么办？使用作用域访问符 `::height`

```
//不建议的写法：不要隐藏外层作用域中可能被用到的名字
    void Screen::dummy_fcn(pos height){
        cursor = width * ::height; //哪个 height? 是那个全局变量
    }
```

> Note: 尽管外层的对象被隐藏掉了，但仍然可以通过作用域运算符来访问它。





#### 在文件中名字的出现处对其进行解析

成员定义在类外部时，名字查找的第三步不仅考虑类定义之前的全局作用域中的声明，还需要考虑在成员函数定义前的全局作用域中的声明。

```
#include<iostream>
using namespace std;

// 定义在类外的成员函数，名字查找顺序：考虑类前作用域、考虑方法定义前的作用域
int height;  //定义了一个名字，稍后在Screen 中使用
class Screen{
public:
    typedef std::string::size_type pos;
    void setHeight(pos);
    pos height = 0; //隐藏了外层作用域中的同名 height
};

Screen::pos verify(Screen::pos);

//全局函数 verify 的声明在类的定义前是不可见的。然而，名字查找的第三步，包括了成员函数定义前的全局作用域。
// 该例中，verify 声明出现在定义 setHeight 前，可以正常访问
void Screen::setHeight(pos var){
    // var: 参数
    // height: 类的成员
    // verify: 全局函数
    height = verify(var);
}

int main(){
    Screen scr1;
    scr1.setHeight(25);
    cout << scr1.height << endl;

    return 0;    
}

Screen::pos verify(Screen::pos ht){
    if(ht>1e4){
        return 1e4;
    }
    return ht;
}

$ g++ b15_var_in_class.cpp 
$ ./a.out 
25
```












## 7.5 构造函数再探

### 7.5.1 构造函数初始值列表
























































## 7.6 类的静态成员



































