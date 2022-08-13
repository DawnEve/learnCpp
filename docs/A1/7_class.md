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









### 7.1.4 构造函数



































## 7.2 访问控制与封装



































## 7.3 类的其他特性



































## 7.4 类的作用域



































## 7.5 构造函数再探



































## 7.6 类的静态成员



































