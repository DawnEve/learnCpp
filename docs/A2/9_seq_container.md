# 第9章 顺序容器

是第三章(字符串、向量和数组)的扩展。

- 顺序容器(sequential container)，加入顺序和在容器中的顺序一致
- 关联容器(第11章)，元素位置由相关联的关键字决定。类似py字典
- 所有容器类都共享公共的接口，方便学习。
    * 不同容器，提供了不同的性能和功能的权衡。
- 标准库还提供了了三种容器适配器。





## 9.1 顺序容器概述

- 性能折中
    * 向容器中添加或从容器删除元素的代价
    * 非顺序访问容器中元素的代价


- 表 9.1 顺序容器类型
    * vector 可变大小的数组。支持快速随机访问。在尾部之外的位置添加或删除元素可能很慢。
    * deque 双端队列。支持快速随机访问。从头尾位置插入、删除速度很快。
    * list 双向链表。只支持双向顺序访问。在list中任何位置进行插入、删除操作都很快。
    * forward_list 单向链表。只支持单向顺序访问。在链表任何位置进行插入、删除操作速度都很快。
    * array 固定大小数组。支持快速随机访问。不能添加或删除元素。
    * string 与 vector 相似的容器，但专用于保存字符。随机访问快。在尾部插入、删除速度快。


> 通常，使用 vector 是最好的选择，除非你有很好的理由选择其他容器。


一些选择容器的基本原则:

- 优先 vector，除非有其他更好的理由。
- 很多小元素，且空间的额外开销很重要，则不要使用list或forward_list;
- 要求随机访问，应使用 vector 或 deque
- 要求在容器中间插入或删除元素，使用 list 或 forward_list
- 需要在头尾插入或删除元素，但不会在中间位置进行插入或删除，则使用 deque
- 如果只在读取时才需要在容器中间位置插入元素，随后需要随机访问元素，则
    * 首先，确定是否真的需要在容器中间插入元素。当处理输入数据时，通常可以很容易的向vector 追加数据，然后再调用标准库的sort函数重拍容器中的元素，从而避免在中间添加元素；
    * 如果必须在中间插入元素，考虑在输入阶段使用list，输入完成后，将list内容拷贝到 vector中。


> 通常随机访问(vector/deque)和中间位置插入元素、删除元素(list/forward_list)是互斥的，不可能都快，取决于占主导地位的操作。

> 不确定使用哪种容器时，可以只使用 vector 和 list 公共的操作：使用迭代器，不使用下标操作，避免随机访问。这样必要时可以更换 vector 或 list。















## 9.2 容器库概览

- 有些操作是所有容器都提供的(P295, 表9.2)
- 另一些仅针对顺序容器(表9.3, P299)、关联容器(表11.7, P388)或无序容器(表11.8, P395)
- 还有一些操作是一小部分容器特有的

本节讲所有容器共有的操作。本章其余部分讲仅适用于顺序容器的操作。关联容器在11章讲。


每个容器都定义在一个头文件，文件名和类型名相同。

- deque 定义在 deque 头文件中
- list 定义在 list 头文件中

对于 vector 还需要提供类型信息来生成特定的容器类型:

```
list<Sales_data> //保存 Sales_data 对象的list
deque<double> //保存double的deque
```




#### 对容器可以保存的元素类型的限制

顺序容器几乎可以保存任意类型的元素。甚至是另一个容器。

```
vector<vector<string>> lines; //vector 的vector
```

> 在老编译器上，最后的两个尖括号之间要有空格: `vector<vector<string> >`


没有默认构造函数的，必须需要传入初始化值。

```
//假定 noDefault 是一个没有默认构造函数的类型
vector<noDefault> v1(10, init); //正确: 提供了元素初始化器
vector<noDefault> v2(10); //错误: 必须提供一个元素初始化器
```



- 表9.2 容器操作(P295)
- 类型别名
    * iterator 此容器类型的迭代器类型
    * const_iterator 可以读取元素，但是不能修改元素的迭代器类型
    * size_type 无符号整数类型，足够保存该种容器类型最大可能容器的大小
    * difference_type 带符号整型，足够保存2个迭代器之间的距离
    * value_type 元素类型  //todo
    * reference 元素的左值类型：与 value_type& 含义相同  //todo
    * const_reference 元素的const左值类型(即 const value_type& )  //todo
- 构造函数
    * C c; 默认构造函数，构造空容器(array, P301)
    * C c1(c2); 构造c2的拷贝c1
    * C c(b, e); 构造c，将迭代器b和e指定的范围内的元素拷贝到c(array 不支持)
    * C c(a, b, c...); 列表初始化c
- 赋值与 swap
    * c1=c2; 将c1中的元素替换为c2中的元素 //todo
    * c1={a, b, c...}; 将c1中的元素替换为列表中的元素(不适用于 array)
    * a.swap(b);  交换a和b的元素
    * swap(a,b); 同a.swap(b);
- 大小
    * c.size(); c中元素的数目(不支持 forward_list)
    * c.max_size(); c 可保存的最大元素数
    * c.empty(); 若c中存储了元素，返回false，否则返回true
- 添加/删除元素(不是用于 array) 注: 不同容器中，这些操作的接口都不同
    * c.insert(args);  将args 中的元素拷贝进c
    * c.emplace(inits);  使用 inits 构造c中的一个元素
    * c.erase(args);  删除args指定的元素
    * c.clear();   删除c中的所有元素，返回 void
- 关系运算符
    * ==, !=  所有容器都支持相等(不相等)运算符
    * <, <=, >, >=  关系运算符(无序容器不支持)
- 获取迭代器
    - c.begin(), c.end()    返回指向c的首元素和尾后位置的迭代器
    - c.cbegin(), c.cend()    返回 const_iterator
- 反向容器的额外成员(不支持 forward_list)
    * reverse_iterator      按逆序寻址元素的迭代器
    * const_reverse_iterator        不能修改元素的逆序迭代器
    * c.rbegin(), c.rend();     返回指向c的尾元素和首元素之前位置的迭代器
    * c.crbegin(), c.crend();     返回 const_reverse_iterator




### 9.2.1 迭代器

- 与容器一样，迭代器有着公共的接口：
    * 迭代器可以访问容器中的元素，通过解引用操作
    * 迭代器都可以递增，从而指向下一个元素
    * 表3.6(P96)列出了容器迭代器支持的所有操作，其中一个例外不符合公共接口特定: forward_list 迭代器不支持递减运算符(be--)
    * 表3.7(P99)列出了迭代器支持的算术运算，这些运算只能用于 string, vector, deque 和 array 的迭代器。

#### 迭代器范围 iterator range

> 迭代器范围的概念是标准库的基础。

iterator range 是一对迭代器分别指向首元素和尾后位置(one past the last element)，通常叫做 begin 和 end。(first 和 last 有误导性，因为是last的下一个位置)，他们标记了容器中元素的一个范围。左闭合区间（left-inclusive interval），数学描述为 [begin, end)

- 对构成范围的迭代器的要求
    * 指向同一个容器中的元素或者最后一个元素的下一个位置，且
    * 可以通过begin反复递增达到end，换句话说，begin在end前面。
    * 这些需要程序员负责，编译器不会强制。


#### 左闭右开区间的编程假设

- 如果begin和end 相等，则范围为空
- 如果不等，则至少包含一个元素，且begin指向第一个元素
- 可以通过begin递增若干次，达到 begin==end


这就意味着，我们可以安全的写循环，并通过递增，最后肯定能结束循环:

```
while(begin != end){
    *begin=val;  //正确：范围非空，则begin指向一个元素
    ++begin;   //移动迭代器，指向下一个元素
}
```




### 9.2.2 容器类型成员

每个容器都定义了多个类型，如表9.2(P295)。已经使用过 `size_type`(3.2.2, P79)、`iterator`和`const_iterator`(3.4.1, P97)

大多数容器还提供了`反向迭代器`，对反向迭代器执行++操作，得到上一个元素(10.4.3, P363)


- 类型别名，可以在不了解容器中元素类型的情况下使用它。
    * 如果需要元素类型，可以使用容器的 value_type。
    * 如果需要元素类型的一个引用，可以使用 reference 或 const reference。
    * 这些元素相关的类型别名在泛型编程中非常有用，见第16章。


为了使用这些类型，我们必须显式使用其类名:
```
// iter 是通过 list<string> 定义的一个迭代器类型
list<string>::iterator iter;
//count 是通过 vector<int> 定义的一个 difference_type 类型
vector<int>::diffenrence_type count;
```

这些声明语句使用了作用域运算符(1.2, P7)来说明，我们希望使用 `list<string>`类的 iterator 成员，及`vector<int>`类定义的difference_type。





### 9.2.3 begin 和 end 成员

begin 和 end 操作生成指向容器中第一个元素和尾后元素的迭代器。最常见用途是形成一个包含容器中所有元素的迭代器范围。

不以c开头的函数都是被重载过的。也就是说，有2个 begin 的成员。一个是 const 成员，返回容器的 const_iterator 类型。另一个是非常量成员，返回容器的 iterator 类型。

以 c 开头的版本是C++新标准引入的，用以支持 auto 与 begin 和 end 函数结合使用。

当 auto 与 begin 和 end 结合使用时，获得的迭代器类型依赖于容器类型，与我们想要如何使用迭代器不相干。但以c开头的版本还是可以获得 const_iterator 的，而不管容器的类型是什么。

> 当不需要写访问时，应使用 cbegin 和 cend。






### 9.2.4 容器定义和初始化

- 每个容器类型都定义了一个默认构造函数(7.1.4, P236)
    * 除array之外，其他容器的默认构造函数都会创建一个指定类型的空容器，且都可以接受指定容器大小和元素初始值的参数。

- 表 9.3 容器定义和初始化
    * C c;   默认构造函数。如果C是一个array，则c中元素按默认方式初始化；否则c为空。
    * C c1(c2);   c1初始化为c2的拷贝。c1和c2必须是相同类型(相同容器类型，且保存相同的元素类型；对于array类型，还必须大小相同)
    * C c1=c2;    同上；
    * C c{a, b, c...};   c 初始化为初始化列表中元素的拷贝。列表中元素的类型必须与C的元素类型相容。对于array类型，列表中元素数目必须等于或小于array的大小，任何遗漏的元素都进行值初始化(3.3.1, P88)
    * C c={a, b, c...};  同上
    * C c(b, e);  c初始化为迭代器b和e指定范围中的元素的拷贝。范围中的元素类型必须与C的元素类型相容(array 不适用)
    * 只有顺序容器(不包括array)的构造函数才能接受大小参数
    * C seq(n);   seq 包含 n 个元素，这些元素进行了值初始化；此构造函数是 explicit 的(7.5.4, P265)。(string 不适用)
    * C seq(n, t);  seq 包含n个初始化为值t的元素




#### 将一个容器初始化为另一个容器的拷贝

- 方法1: 直接拷贝整个容器。容器类型和元素类型必须匹配。
- 方法2: (array除外)拷贝由一个迭代器对指定的元素范围。不要求容器类型是相同的，只要元素类型相容(相同或可转换)即可。(4.11, P141)


```
// 每个容器有三个元素，用给定的初始化器进行初始化
list<string> authors = {"Milton", "Shakespears", "Austen"};
vector<const char*> articles = {"a", "an", "the"};

list<string> list2(authors); //正确：类型匹配
//deque<string> authList(authors); //错误: 容器类型不匹配
// error: no matching function for call to ‘

//vector<string> words(articles);  //错误: 容器类型必须匹配
//error: no matching function for call to

// 正确，可以将 const char* 元素转换为 string
forward_list<string> words(articles.begin(), articles.end());
```

> 当一个容器初始化为另一个容器的拷贝时，两个容器的容器类型和元素类型都必须相同。

由于2个元迭代器表示一个范围，因此可以使用这种构造函数来拷贝一个容器中的子序列。

```
// 迭代器 it 指向 authors 中的一个元素，则拷贝到 it(不包括)指向的元素
deque<string> authList(authors.begin(), it);
```



#### 列表初始化

- 显式指定容器中的每个元素的值
- 除了array之外的容器类型，初始化列表还隐含的指定了容器的大小：容器将包含与初始值一样多的元素。

```
// 每个元素三个元素，用给定的初始化器进行初始化
list<string> authors = {"Milton", "Shakespeare", "Austen"};
vector<const char*> articles={"a", "an", "the"};
```



#### 与顺序容器大小相关的构造函数

除了与关联容器相同的构造函数外，顺序容器（array除外）还提供了另一个构造函数，接受一个容器大小，一个（可选的）元素初始值。

- 如果不提供初始值，则标准库会创建一个值初始化器(3.3.1, P88)
- 如果元素类型没有默认构造函数，则必须显式提供一个初始值。

```
vector<int> ivec(10, -1);      //10个int元素，每个都初始化为-1
list<string> svec(10, "hi!");   //10个strings; 每个都初始化为 "hi!"
forward_list<int> ivec2(10);    //10个元素，每个都初始化为0
deque<string> svec2(10);   //10个元素，每个都是空string
```

> 只有顺序容器的构造函数才接受大小参数，关联容器不支持。




#### 标准库 array 具有固定大小

与内置大小一样，标准库array的大小也是类型的一部分。

```
// 定义array时，要指定元素类型，还要指定容器大小
array<int, 10>  //类型为: 保存10个int的数组
array<string, 15>  //类型为: 保存15个string的数组
```

为了使用 array 类型，我们必须同时指定元素类型和大小:

```
array<int, 10>::size_type i;   //数组类型包括元素类型和大小
array<int>::size_type j;       //错误：array<int>不是一个类型
```

> 由于大小是array类型的一部分，array不支持普通的容器构造函数。 这些函数都会确定容器的大小，显示或隐式地。而允许用户向一个array构造函数传递大小参数，最好的情况下也是多余的，而且容易出错。


- array 大小固定的特性也影响了他所定义的构造函数的行为。与其他容器不同，一个默认的构造函数的 array 是非空的：它包含了其大小一样多的元素。这些元素都默认初始化，就像一个内置数组中的元素那样。
    * 列表初始化时，提供的元素必须小于或等于array的大小。
    * 当提供的值少时，后面的进行值初始化。
    * 如果元素是一个类类型，该类必须有一个默认构造函数，以便值初始化能进行。

```
array<int, 10> ia1;   //10个默认初始化的int
array<int, 10> ia2 = {0,1,2,3,4,5,6,7,8,9}; //列表初始化
array<int, 10> ia3 = {5};  //ia3[0]为5，其余为0
```

> 虽然不能对内置数组类型进行拷贝或者对象赋值操作(3.5.1, P102)，但 array 并无此限制。

```
    int arr[]={1,2,3};
    //int arr2[3]=arr;//error: array must be initialized with a brace-enclosed initializer
    int arr3[3];
    //arr3=arr;  // 错误: 内置数组不支持拷贝或赋值
    //error: invalid array assignment

    // part2
    array<int, 3> arrB={1,2,3};
    array<int, 3> arrB2=arrB; //正确：只要数组类型匹配即合法
```







### 9.2.5 赋值和swap

赋值

```
c1=c2;  //将c1的内容替换为c2中元素的拷贝。赋值后两者大小相等
c1={a,b,c}; //赋值后，c1大小为3
```

例:

```
#include<iostream>
#include<list>
using namespace std;

// 赋值
int main(){
    list<int> c1={1,2,3};

    // 1.拷贝
    list<int> c2=c1;

    for(auto i: c2)
        cout << i << ", ";
    cout << endl;

    // 2.赋值
    c2={1,2,3,4,5};

    for(auto i: c2)
        cout << i << ", ";
    cout << endl;

    return 0;
}

$ g++ a9_assign.cpp 
$ ./a.out 
1, 2, 3, 
1, 2, 3, 4, 5,
```





与内置数组不同，标准库的 array 类型允许赋值。

```
array<int, 5> a1={0,1,2,3,4};
array<int, 5> a2={0};  //所有元素都是0
a2=a1;  //替换a2中的元素，变为a1的拷贝
a2={-50};  //错误: 不能将一个花括号列表赋值给array  //注: 我认为作者写错了，这里不报错，是把a2元素归零，首元素设为-50。
```

例:

```
#include<iostream>
#include<array>
using namespace std;

// array 可以赋值
int main(){
    array<int, 5> arr1={0,1,2,3,4};
    array<int, 5> arr2={0};

    // arr1
    cout << arr1.size() << endl;
    arr2=arr1;
    cout << arr1.size() << endl;

    for(auto i: arr1)
        cout << i << " ";
    cout << endl;

    // arr2
    arr2={0}; //不报错，不变长度。其他容器变长度
    for(auto i: arr2)
        cout << i << " ";
    cout << endl;

    return 0;
}


$ g++ a10_array_assign.cpp 
$ ./a.out 
5
5
0 1 2 3 4 
0 0 0 0 0
```


- 表9.4: 容器赋值运算
    * c1=c2;  将c1中的元素替换为c2中元素的拷贝。c1和c2必须具有相同的类型
    * c={a,b,c...};   将c1中的元素替换为初始化列表中元素的拷贝(array 不适用) //注: 我的测试array使用
    * swap(c1, c2);  交换c1和c2中元素。c1和c2必须具有相同的类型。swap通常比从c2向c1拷贝元素快得多。
    * c1.swap(c2);  同上
    * assign 操作符不适用于关联容器和 array
    * seq.assign(b,e);   将seq中的元素替换为迭代器b和e所表示的范围中的元素。迭代器b和e不能指向seq中的元素
    * seq.assign(il);   将seq中的元素替换为初始化列表 il 中的元素
    * seq.assign(n,t);  将seq中的元素替换为n个值为t的元素

> 赋值相关运算会导致指向左边容器内部的迭代器、引用和指针失效。而swap操作将容器内容交换不会导致指向容器的迭代器、引用和指针失效(容器类型为array和string的情况除外)。


例: swap的用法

```
#include<iostream>
#include<list>
using namespace std;

void print(const list<int> &l0){
    cout << ">> &l0: " << &l0 << endl;
    for(auto i: l0)
        cout << i << " ";
    cout << endl;
}


// swap 的使用
int main(){
    list<int> l1={0,1,2};
    list<int> l2={0,10,20};

    //l1.swap(l2);
    swap(l1, l2);
    cout << "&l1: " << &l1 << endl;
    cout << "&l2: " << &l2 << endl;
    print(l1);
    print(l2);

    return 0;
}

$ g++ a11_swap.cpp 
$ ./a.out 
&l1: 0x7ffc6504d860
&l2: 0x7ffc6504d880
>> &l0: 0x7ffc6504d860
0 10 20 
>> &l0: 0x7ffc6504d880
0 1 2 
```



#### 使用 assign (仅顺序容器)

赋值运算符要求左边和右边的对象具有相同的类型。

顺序容器(array除外)还定义了一个 assign 函数，允许从一个不同但是相容的类型赋值，或者从容器的一个子序列赋值。

assign 操作用参数所指定的元素(的拷贝)替换左边容器中的所有元素。


例: 用 assign 实现将一个 vector 中的一段 char* 值赋予一个 list 的string

```
list<string> names;
vector<const char*> oldStyle;
names = oldStyle; //错误：容器类型不匹配

//正确: 可以将 const char* 转换为 string
names.assign(oldStyle.cbegin(),  oldStyle.cend());
```


assign 的第二个版本接受一个整型值和一个元素值。它用指定数目且具有相同给定值的元素替换容器中原有的元素:

```
// 等价于 slist1.clear()
// 后跟 slist1.insert(slist1.begin(), 10, "Hiya!");
list<string> slist1(1);      //1个元素，为空string
slist1.assign(10, "Hiya!");  //10个元素，每个都是 "Hiya!"
```



例2: assign 的三种用法

```
#include<iostream>
#include<vector>
#include<list>

using namespace std;

void print(list<string> l1){
    for(auto i: l1)
        cout << i << " ";
    cout << endl;
}

// assign 的用法
int main(){
    list<string> names;
    vector<const char*> oldStyle = {"Hi!", "How", "are", "you?"};
    //names = oldStyle; //错误：容器类型不匹配
    //error: no match for ‘operator=’

    //正确: 可以将 const char* 转换为 string
    names.assign(oldStyle.cbegin(),  oldStyle.cend());
    print(names);

    // 用法2: 列表
    names.assign( {"this", "is", "a", "book"} );
    print(names);

    // 用法3: (n,t) 填充为n个值为t的元素
    names.assign(3, "is");
    print(names);

    return 0;
}



$ g++ a12_assign.cpp 
$ ./a.out 
Hi! How are you? 
this is a book 
is is is
```


> 由于其旧元素被替换，因此传递给 assign 的迭代器不能指向调用 assign 的容器。





#### 使用 swap

```
vector<string> svect1(10);  //10个元素的string
vector<string> svect2(24);  //24个元素的string
swap(svect1, svect2);
```

交换后，svect1将有24个string元素，svect2将有10个string元素。

除array外， 交换两个容器内容的操作保证会很快：元素本身并未交换，swap 只是交换了2个元素的内部数据结构。

```
#include<iostream>
#include<vector>
using namespace std;

//swap 没有交换元素，只是交换了容器的内部数据结构
int main(){
    vector<string> svect1(10);  //10个元素的string
    vector<string> svect2(24);  //24个元素的string

    cout << "addr Bef: " << &svect1[2] << " " << &svect2[2] << endl;
    swap(svect1, svect2);
    cout << "addr Aft: " << &svect1[2] << " " << &svect2[2] << endl;

    cout << svect1.size() << endl;
    cout << svect2.size() << endl;

    return 0;
}


$ g++ a13_swap_addr.cpp 
$ ./a.out 
addr Bef: 0x56080c177ef0 0x56080c178040
addr Aft: 0x56080c178040 0x56080c177ef0
24
10
```


> 除 array 外，swap 不对任何元素进行拷贝、删除或插入操作，因此可以保证在常数时间内完成。

- 与其他容器不同，swap两个array会真正交换它们的元素。因此，交换2个array所需的时间与array中元素的数目成正比。

例: 测试 swap array 是否拷贝元素？

```
#include<iostream>
#include<array>
using namespace std;

//swap 没有交换元素，只是交换了容器的内部数据结构：array 是例外
int main(){
    array<string, 3> svect1={"hi", "how", "are"};
    array<string, 3> svect2={"this", "is", "book"};

    cout << "addr Bef: " << &svect1[2] << " " << &svect2[2] << endl;
    swap(svect1, svect2); // 对于array，swap后元素的地址不变，就是发生了拷贝
    cout << "addr Aft: " << &svect1[2] << " " << &svect2[2] << endl;

    for(auto i : svect1)
        cout << i << " ";
    cout << endl;

    return 0;
}

$ g++ a14_swap_array_addr.cpp 
$ ./a.out 
addr Bef: 0x7ffddd940ab0 0x7ffddd940b10
addr Aft: 0x7ffddd940ab0 0x7ffddd940b10
this is book
```



元素不被移动，就意味着，除string外，指向容器的迭代器、引用和指针在swap操作后都不会失效。他们仍然指向swap 操作之前所指向的那些元素。但是，swap后，这些元素属于不同的容器了。

- 与其他容器不同，对于 string 调用 swap 会导致迭代器、引用和指针失效。 //我的测试是不失效。`9/a15_swap_string.cpp`
- 因此，对于 array，在 swap 操作之后，指针、引用和迭代器所绑定的元素保持不变，但是元素值已经与另一个array中对应元素的值进行了交换。
- 新标准中，容器既提供成员函数版本的swap，也提供非成员版本的swap。后者在泛型编程中是非常重要的。统一使用非成员版本的 swap 是一个好习惯。


> 如何通过迭代器获取元素的地址？auto be=c1.begin(); `*be`是元素，则 `&*be` 是元素的地址。

```
#include<iostream>
#include<vector>
#include<list>
using namespace std;

// 通过迭代器获取元素的地址
/*不能直接取迭代器的地址
对迭代器加*，即获得该迭代器所指的元素
对迭代器加*，再加&，就是该元素的地址 */
int main(){
    vector<int> arr1={1,2,3};
    list<int> l2={-1,-2,-3};

    // 一个元素只占用4位
    auto be1=arr1.begin();
    while(be1 != arr1.end()){
        cout << &*be1 << ": " << *be1 << endl;
        be1++;
    }
    cout << endl;

    // list 确实很消耗内存，一个元素占用 f00-ee0 = 32位 = 4+8+8+?: 一个int是4,2个指针是2*8，还有 12 是啥占用的？
    auto be2=l2.begin();
    while(be2 != l2.end()){
        cout << &*be2 << ": " << *be2 << endl;
        be2++;
    }
    cout << endl;
    cout << 0xf00 - 0xee0 << endl;

    return 0;
}

$ g++ a17_get_addr_by_iterator.cpp 
$ ./a.out 
0x5594ef290eb0: 1
0x5594ef290eb4: 2
0x5594ef290eb8: 3

0x5594ef290ee0: -1
0x5594ef290f00: -2
0x5594ef290f20: -3

32
```








### 9.2.6 容器大小操作

- 成员函数 size() 返回容器中元素的个数
- empty() 当size为0时返回布尔值true，否则返回 false
- max_size() 返回一个大于或等于该类型容器所能容纳的最大元素数的值。

forward_list 支持 max_size 和 empty，但不支持 size。






### 9.2.7 关系运算

- 每个容器都支持相等运算符: `==` 和 `!=`
- 除了无序关联容器，都支持 关系运算符: `>`, `>=`, `<`, `<=`
    * 相同类型的容器，且保存相同类型的元素，才能做关系运算: `vector<int>` 和 `vector<int>`比较，而布恩那个和另一个 `vector<double>`做比较。
    * 实际上是元素的逐对比较。这与string的关系运算符的工作方式类似:
        - 如果大小相同，每个元素相同则相等，否则不等；
        - 如果大小不同，但小容器中每个元素都和大容器一一相等，则小容器小于较大容器
        - 如果两个容器都不是另一个容器的前缀子序列，则它们的大小取决于第一个不等元素的比较结果。


```
#include<iostream>
#include<vector>
using namespace std;

// 关系运算符
int main(){
    vector<int> v1={1,3,5,7,9,12};
    vector<int> v2={1,3,9};
    vector<int> v3={1,3,5,7};
    vector<int> v4={1,3,5,7,9,12};
    cout << (v1<v2) << endl; //true; 第一个不等的元素 5<9
    cout << (v1<v3) << endl; //false: 已有元素都相等，但是v1长
    cout << (v1==v4) << endl; //true：每个元素都相等
    cout << (v1==v2) << endl; //false: 数目不等

    return 0;
}

$ g++ a16_equal.cpp 
$ ./a.out 
1
0
1
0
```





#### 容器的关系运算符使用元素的关系运算符完成比较

> 只有当其元素类型也定义了相应的比较运算符时，我们才可以使用关系运算符来比较2个容器。

- 容器的相等是使用元素的`==`运算符来完成的
- 其他关系运算符是使用元素的`<`运算符。

如果元素不支持所需运算符，那么保存这种元素的容器就不能使用响应的关系运算。


```
vector<Sales_data> storeA, storeB;
if ( storeA < storeB ) //错误: Sales_data 没有定义<运算符
```














## 9.3 顺序容器操作


### 9.3.1 向顺序容器添加元素

除array外，所有标准库容器都提供灵活的内存管理。运行时可以灵活添加或删除元素来改变容器大小。

- 表 9.5 向顺序容器添加元素的操作 
    * 这些操作会改变容器的大小；array 不支持这些操作
    * forward_list 有自己专有版本的 insert 和 emplace；见 9.3.4，P312
    * forward_list 不支持 push_back 和 emplace_back;
    * vector 和 string 不支持 push_front 和 emplace_front
    * c.push_back(t)    在 c 的尾部创建一个值为t或由 args 创建的元素，返回 void
    * c.emplace_back( args)  同上
    * c.push_front(t)   在 c 的头部创建一个值为t或由 args 创建的元素，返回 void
    * c.emplace_front(args)  同上
    * c.insert(p, t)   在迭代器 p 指向的元素之前创建一个值为t或由 args 创建的元素。返回指向新添加的元素的迭代器。
    * c.emplace(p, args)    同上
    * c.insert(p, b, e)    将迭代器 b 和 e 指定的范围内的元素插入到迭代器 p 指向的元素之前。b和e不能指向c中的元素。返回指向新添加的第一个元素的迭代器；若范围为空，则返回p。
    * c.insert(p, il)    il 是一个花括号包围的元素的值列表。将这些给定值插入到迭代器p指向的元素之前。返回指向新添加的第一个元素的迭代器；若列表为空，则返回p。

> 向一个 vector、string或 deque 插入元素会使所有指向容器的迭代器、引用和指针失效。


- 牢记分配元素空间的机理，防止影响性能
    * 在 vector 或 string 的尾部之外的任何位置，或是一个 deque 的首尾之外的任何位置添加元素，都要移动元素
    * 向一个 vector 或 string 添加元素可能引起整个对象存储空间的重新分配：新建内存，并把旧元素移动到新的内存空间。




#### 使用 push_back 

- 此前用过，把元素添加到vector末尾，用过 push_back。
- 除了 array 和 forward_list 之外，每个顺序容器（包括string类型）都支持 push_back

```
// 每个循环读取一个string到word，然后追加到容器尾部
string word;
while(cin >> word)
    containner.push_back(word);
```

- 对 push_back 的调用在 container 尾部创建了一个新元素，将 containner 的 size 增大了1。
- 该元素的值为 word 的一个拷贝。
- containner 的类型可以是 list, vector 或者 deque

由于 string 是一个字符容器，也可以用 push_back在 string 末尾添加字符：

```
void pluralize(size_t cnt, string &word){
    if(cnt>1)
        word.push_back('s'); //等价于 word += 's';
}
```


> 关键概念：容器元素是拷贝。





#### 使用 push_front 

除了 push_back, list、forward_list 和 deque 容器还支持名为 push_front 的类似操作。把元素插入到容器头部。

```
list<int> ilist;
//将元素添加到ilist开头
for(size_t ix=0; ix!=4; ++ix){
    ilist.push_front(ix);
}
```

- 循环把元素 0,1,2,3 添加到 ilist 头部。因此打印的时候，是倒序的。

注意: deque 像 vector 一样提供了随机访问元素的能力，但它提供了 vector 所不支持的 push_front。

- deque 在首尾插入和删除元素耗时是常数时间。与 vector 一样，在 deque 首尾之外的位置插入会很耗时。





#### 在容器的特定位置添加元素： insert 

- insert 能在任意位置插入0个或多个元素。
- vector/ deque/ list 和 string 都支持 insert 成员。
- forward_list 提供了特殊版本的 insert 成员: P312, 9.3.4


每个 insert 函数都接受一个迭代器作为参数一。迭代器指定什么位置放置新元素。可以是任何位置，包括尾后位置。插入位置是迭代器指向位置之前。

```
slist.insert(iter, "hello!"); //将 "hello!" 添加到 iter 之前的位置
```


虽然某些容器不支持 push_front 操作，但它们对于 insert 操作并无类似的限制（插入开始位置）。因此可以使用 insert 把元素插入开头位置，而不用担心容器是否支持 push_front:

```
list<string> slist;
vector<string> svect;

//等价于 
slist.push_front("list.");
slist.insert(slist.begin(), "Hello!");

// vector 不支持 push_front，但是也可以插入 begin() 之前
// 警告：插入到 vector 末尾之外的位置都可能很慢
svect.insert(svect.begin(), "vect");
svect.insert(svect.begin(), "Hello!");
```


> 警告：将元素插入到 vector、deque和string中的任何位置都是合法的。也可能是耗时的。





#### 插入范围内元素

insert 除了接收一个指向自己的迭代器作为第一个参数，还可以接受更多参数。类似容器构造函数。


例1: 接受一个元素数目和一个值，将指定个数的值插入到迭代器指定位置之前，这些元素给定值初始化:

```
// 将 3个字符串 "Tomcat" 插入到 svect 的尾后位置之前
svect.insert(svect.end(), 3, "Tomcat");
```


例2: 接受一对迭代器或一个初始化列表的insert版本，经给定范围中的元素插入到指定位置之前

```
vector<string> source={"this", "is", "a", "book"};
vector<string> svect={"dest"};
//把source的最后2个元素插入到svect的末尾
svect.insert(svect.end(), source.end()-2, source.end()); 

// 传入一个初始化列表
svect.insert(svect.end(), {"hi", "Tomcat"});
```

书上说，第2和3个参数是一对迭代器时，不能指向第一个迭代器指向的对象，我测试的至少没有报错:

```
例2:
    vector<string> svect={"dest", "nobug"};
    //把source的最后2个元素插入到svect的末尾
    print(svect);
    svect.insert(svect.end(), svect.begin()-2, svect.end()); // 啥也没做

例2:
    list<string> slist={"dest", "A"};
    // $ g++ -std=c++11 b5_insert_iter_num_val.cpp
    // $ ./a.out
    // dest A dest A  #没有报错.... 
    slist.insert(slist.end(), slist.begin(), slist.end()); //正常插入
```





#### 使用 insert 的返回值

- 新版本，接收元素个数或范围的insert版本返回指向第一个新加入元素的迭代器。（旧版本返回void）
- 如果范围为空，不插入任何元素，返回insert的第一个参数。

```
void demo1(){
    vector<string> svect={"hi"};
    auto xx = svect.insert(svect.end(), 3, "Tomcat");
    cout << *xx << ", " << &*xx << endl;

    auto be=svect.begin();
    cout << *be << ", " << &*be << endl;
    be++;
    cout << *be << ", " << &*be << endl;
}

输出:
Tomcat, 0x5649d5b8ff00
hi, 0x5649d5b8fee0
Tomcat, 0x5649d5b8ff00
```


通过使用  insert 的返回值，可以在容器中一个特定位置反复插入元素:

```
// 通过insert的返回值，在一个位置反复插入元素
void demo3(){
    list<string> lst={"hello"};
    auto iter=lst.begin();
    string word;
    cout << "Please input some word, end with Ctrl+D" << endl;
    while(cin >> word)
        iter=lst.insert(iter, word); //等价于 push_front
    
    //打印
    for(auto i: lst)
        cout << i << " ";
    cout << endl;
}

输出:
Please input some word, end with Ctrl+D
1 2 34 56
56 34 2 1 hello
```

> Note: 理解这个循环是如何工作的非常重要，特别是理解这个循环为什么等价于调用 push_back 尤为重要。

循环前，iter指向第一个元素。然后每次插入到第一个元素之前，并返回指向新插入的元素的迭代器。所以相当于每次都插入到第一个元素之前。





#### 使用 emplace 操作

新标准引入三个新成员: emplace_front, emplace 和 emplace_back，这些操作构造而不是拷贝元素。对应 push_front, insert 和 push_back，允许我们将元素放置在容器头部、一个指定位置之前或尾部。



- 调用 push 或 insert 成员函数时，我们将元素类型的对象传递给它们，这些对象被拷贝到容器中。
- 当调用 emplace 成员函数时，则是将参数传递给元素类型的构造函数。emplace成员使用这些构造函数在容器管理的内存空间直接构造元素。

```
    // 加入c保存 Sales_data 元素
    list<Sales_data> c;
    // 使用3个参数的 Sales_data 构造函数
    c.emplace_back("978-05", 25, 15.99);
    // 错误：没有接收3个参数的 push_back 版本
    //c.push_back("978-05", 25, 15.99); //error: no matching function for call to
    //正确，创建一个临时的 Sd对象传递给 push_back
    c.push_back( Sales_data("978-05", 25, 16.00) );
```

> emplace 函数的参数根据元素类型而变化，参数必须与元素类型的构造函数相匹配:

```
c.emplace_back(); //使用 Sales_data 的默认构造函数
c.emplace(iter, "99-992"); //使用 Sales_data(string)
//使用 Sales_data(string, int, double) 的构造函数
c.emplace_front("985-1", 2, 12.99);
```










### 9.3.2 访问元素

如果容器中没有元素，访问操作的结果是未定义的。

- 包括 array 在内的每个顺序容器都有一个 front 成员函数
- 除了 forward_list 之外的所有顺序容器都有一个 back 成员函数。
- 这2个操作分别返回首元素和尾元素的引用。

```
#include<iostream>
#include<list>
using namespace std;

int main(){
    list<int> c={1, 6};
    //在解引用一个迭代器或者front或back前检查是否有元素
    if(!c.empty()){
        // val 和 val2 是c中第一个元素值的拷贝
        auto val=*c.begin(), val2=c.front();
        cout << val << ": " << &*c.begin() << ", " 
             << val2 << ": " << &c.front() << endl; //地址确实一样

        // val3和 val4 是c中最后一个元素值的拷贝
        auto last = c.end();
        auto val3=*(--last); //不能递减 forward_list 迭代器
        auto val4=c.back(); // forward_list 不支持
        cout << val3 << ": " << &*last << ", " 
             << val4 << ": " << &c.back() << endl; //地址确实一样
    }

    return 0;
}


$ g++ b8_front_back.cpp 
$ ./a.out 
1: 0x5637bbff2ec0, 1: 0x5637bbff2ec0
6: 0x5637bbff2ee0, 6: 0x5637bbff2ee0
```

- 1. 迭代器 end()指向尾后位置，是不存在的，不能直接解引用。
- 2. 调用 front 或 end 前，要先检查容器不能为空。


- 表9.6 在顺序容器中访问元素的操作
    * at 和 下标操作只使用于 string、vector、deque 和 array
    * back 不适用于 forward_list
    * c.back()   返回c的尾元素的引用。若c为空，函数行为未定义
    * c.front()  返回c的首元素的引用。若c为空，函数行为未定义
    * c[n]    返回c中下标为n的元素的引用。n是一个无符号整数。若 n>=c.size()，则函数行为未定义
    * c.at(n)  返回下标为n的元素的引用。如果下标越界，则抛出 out_of_range 异常

> 对一个空容器调用 front 和 back ，就像使用一个越界的下标一样，是一种严重的程序设计错误。




#### 访问成员函数返回的是引用

- front/back/下标/at 返回的都是引用。
- 如果容器是const对象，返回的是const的引用。否则，返回的是普通引用。

```
#include<iostream>
#include<list>
using namespace std;

int main(){
    list<int> c={0,2,4};
    if(!c.empty()){
        c.front() = 12; //将12赋值给第一个引用
        
        auto &v=c.back(); //获取最后一个元素的引用
        v=1024; //改变最后一个元素的值
        auto v2=c.back(); //v2不是一个引用，它是c.back() 的一个拷贝
        v2=0; //未改变c中的元素

        for(auto i: c)
            cout << i << " ";
        cout << endl;
    }

    return 0;
}


$ g++ b9_back_return_refer.cpp 
$ ./a.out 
12 2 1024 
```

可以使用引用来改变原来容器中元素的值。

如果用auto变量来保存这些函数的返回值，而且希望改变元素的值，必须记得将变量定义为引用类型。




#### 下标操作和安全的随机访问

- 提供快速随机访问的容器(strng/vector/deque/array)也都提供了下标运算符（P91, 3.3.3）
- 下标必须“在范围内”，即大于等于0，小于容器的大小。
- 保证下标有效是程序员的责任，编译器不检查这种错误。
- 如果希望确保下标合法，可以使用 `at` 函数。
    * at 函数类似下标运算符，但下标越界时会抛出 out_of_range 异常(P173, 5.6)

```
    vector<string> svec={"this", "is"};
    cout << svec[0] << endl;
    //cout << svec[2] << endl; //运行时错误: svec 中没有这个元素
    // Segmentation fault (core dumped)

    cout << svec.at(1) << endl;
    //cout << svec.at(2) << endl; //抛出一个 out_of_range 异常
    //terminate called after throwing an instance of 'std::out_of_range'
```








### 9.3.3 删除元素

(非 array) 容器也有很多删除元素的方法。

- 表9.7 顺序容器的删除操作
    * 这些操作会改变容器的大小，所以不适用于 array
    * forward_list 有特殊版本的 erase，见P312, 9.3.4
    * forward_list 不支持 pop_back; vector和string 不支持 pop_front
    * c.pop_back()   删除 c 中尾元素。若c为空，则函数行为未定义。函数返回 void
    * c.pop_front()   删除c中首元素。若c为空，则函数行为未定义。函数返回void
    * c.erase(p)    删除迭代器p所指定的元素，返回一个指向被删除元素之后的元素的迭代器。若p指向尾元素，则返回尾后位置。若p是尾后迭代器，则函数行为未定义。
    * c.erase(p, e)  删除迭代器b和e所指定范围内的元素。返回一个指向最后一个被删元素之后元素的迭代器。若e本身是尾后迭代器，则函数也返回尾后迭代器
    * c.clear()  删除c中所有元素。返回void

> 删除 deque 中除首尾位置之外的任何元素都会使所有迭代器、引用和指针失效。指向vecotr或string中删除点之后位置的迭代器、引用和指针都会失效。

> 删除元素的成员函数并不检查其参数。在删除元素之前，程序员必须确保它(们)是存在的。





#### pop_front 和 pop_back 成员函数

- 分别删除首元素和尾元素。
- 与 vector和string 不支持 push_front 一样，这些类型也不支持 pop_front。
- forward_list 不支持 pop_back。
- 不能对一个空容器执行弹出元素操作。

这些操作返回void，如果需要值，请在弹出前保存。

```
while(!ilist.empty()){
    process(ilist.front()); // 对ilist 的首元素进行一些处理
    ilist.pop_front();    //完成处理后删除元素
}
```



#### 从容器内部删除一个元素：erase()

- `c.erase(iter);`
- `c.erase(iter1, iter2);`
- 这2种erase形式都返回指向删除的(最后一个)元素之后位置的迭代器。若i后是j，那么 erase(i) 将返回指向j的迭代器。

```
#include<iostream>
#include<list>
using namespace std;

// c.erase(iter); 删除iter指向的元素，返回指向被删元素下一个位置的
int main(){
    list<int> lst={0,1,2,3,4,5};
    auto it=lst.begin();
    while(it != lst.end()){
        if( *it % 2)  //如果元素为奇数
            it = lst.erase(it); //则删除该元素
        else
            ++it;
    }

    // 打印结果
    for(auto i: lst)
        cout << i << " ";
    cout << endl;

    return 0;
}

$ g++ b12_erase.cpp 
$ ./a.out 
0 2 4
```

- 每一步都先检查是否为奇数，是，就删掉，并将迭代器指向被删掉的元素的下一个元素；如果是偶数，则将迭代器递增，指向下一个位置。




#### 删除多个元素

```
// 删除2个迭代器范围内的元素
// 返回被删元素之后的位置
elem1=slist.erase(elem1, elem2); // 调用后，elem1 == elem2
```

- elem1 指向要删除的第一个元素，elem2 指向要删除的最后一个元素之后的位置。
    * 为什么删除后 elem1 指向的元素还在？还能打印 `*iter1`

- 为了删除一个容器内的所有元素，可以使用 `c.clear();`， 也可以调用 `c.erase(c.begin(), c.end());`









### 9.3.4 特殊的 forward_list 操作

为什么 forward_list 有特殊版本的添加和删除操作？ 考虑从一个单向链表中删除一个元素时发生了什么？

- 删除一个元素会改变序列中的链接。
    * 比如删掉 elem3会改变elem2，elem2原来指向elem3，删除elem3后，elem2指向elem4.
    * 添加或删除一个元素后，我们需要访问其前驱，更新其中的链接。
    * 但 forward_list 是单向链表，没有简单的方法获取其前驱。
- 所以，在一个 forward_list 中添加或删除一个元素的操作，是通过改变给定元素之后的元素来完成的。
    * 这样我们能删除下一个元素，能更新当前元素的链接。

由于这些操作与其他容器上的操作的实现方式不同， forward_list 并未定义 insert/ emplace /erase，而是定义了名为 insert_after, emplace_after, erase_after的操作。

- 为了删除 elem3，应该使用指向 elem2的迭代器调用 erase_after。
- 为了支持这些操作， forward_list 也定义了 before_begin(), 它返回一个 首前(off-the-beginning) 迭代器。
    * 该迭代器允许我们在链表首元素之前并不存在的元素“之后”添加或删除元素（相当于在链表首元素之前添加或删除元素）


- 表9.8: 在 forward_list 中插入或删除元素的操作
    * lst.before_begin()   返回指向链表首元素之前不存在的元素的迭代器。此迭代器不能解引用。
    * lst.cbefore_begin()   同上，但返回的是 const_iterator
    * lst.insert_after(p, t)  在迭代器p之后的位置插入元素。t是一个对象。
    * lst.insert_after(p, n, t)   n是数量
    * lst.insert_after(p, b, e)   b和e是表示范围的一对迭代器(b和e不能指向lst内)
    * lst.insert_after(p, il)    il 是一个花括号列表。
    * 以上 insert_after() 返回一个指向最后一个插入元素的迭代器。如果范围为空，返回p。若p为尾后迭代器，则函数行为未定义。
    * emplace_after(p, args)  使用 args在p指定的位置后创建一个元素。返回一个指向这个新元素的迭代器。若p为尾后迭代器，则函数行为未定义
    * lst.erase_after(p);    删除迭代器p指向的位置之后的元素。
    * lst.erase_after(b, e);  删除迭代器b和e范围内的元素。
    * erase_after() 返回一个指向被删元素后的元素的迭代器，若不存在这样的元素，则返回尾后迭代器。如果p指向lst的尾元素或尾后位置，则函数行为未定义。


当在 forward_list 中添加或删除元素时，我们必须关注2个迭代器：
- 一个指向我们要处理的元素
- 一个指向其前驱


例：从 forward_list 中删除奇数元素

```
#include<iostream>
#include<forward_list>
using namespace std;

int main(){
    forward_list<int> flst={0,1,2,3,4,5};
    auto prev=flst.before_begin(); //第一个元素之前的位置
    auto curr=flst.begin(); //第一个元素

    while( curr != flst.end() ){
        if(*curr % 2)  //当前元素是奇数
            curr=flst.erase_after(prev);  //则删掉，使用其前的迭代器
        else{
            //不是奇数，则2个迭代器都向后移动：前=当前，当前后移
            prev=curr; 
            ++curr;
        }
    }
    //打印结果
    for(auto i: flst)
        cout << i << " ";
    cout << endl;

    return 0;
}

$ g++ b14_forward_list_erase.cpp 
$ ./a.out 
0 2 4
```









### 9.3.5 改变容器的大小

- 可以使用 resize 来增大或缩小容器。array不支持 resize。
- 如果当前大小大于新容量，则容器后的元素都会被删除；
- 如果当前大小小于新大小，会将新元素添加到容器后部。


- 表9.9 顺序容器大小操作
    * resize 不适用于 array
    * c.resize(n)   调整 c 的大小为n个元素。若 `n<c.size()`, 则多出来的元素将被丢弃。若必须添加新元素，对新元素进行值初始化
    * c.resize(n, t)  调整c的大小为n个元素。任何新添加的元素都初始化为t。

> 警告：如果 resize() 缩小容器，则指向被删除元素的迭代器、引用和指针都会失效。对vector/ string/ deque 进行 resize() 可能导致迭代器、指针和引用失效。













### 9.3.6 容器操作可能使迭代器失效

> 警告: 使用失效的迭代器、指针或引用是严重的运行时错误。

- 向容器中添加元素时
    * 如果容器是vector或string，且存储空间被重新分配，则指向容器的迭代器、指针、引用都会失效。如果存储空间未重新分配，则指向插入位置之前的迭代器、指针、引用有效，之后的失效。
    * 对于 deque ，插入首尾位置之外的任何位置都会导致迭代器、指针和引用失效。如果在首尾添加元素，迭代器会失效，但指向存在元素的引用和指针不会失效
    * 对于list和 forward_list，指向容器的迭代器(包括尾后迭代器和首前迭代器)、指针、引用仍有效。
- 从容器中删除元素时，指向给删除元素的迭代器、指针和引用会失效。当我们删除一个元素后：
    * 对于list和 forward_list，指向容器其他位置的迭代器、引用和指针仍有效
    * 对于 deque，如果在首尾之外的任何位置删除元素，name指向被删除元素之外的其他元素的迭代器、引用或指针也会失效。如果是删除deque的尾元素，则尾后迭代器也会失效，但其他迭代器、引用和指针不受影响；如果删除首元素，这些也不受影响。
    * 对于 vector 和 string，指向被删元素之前元素的迭代器，引用和指针仍然有效。
    * 注意：我们删除元素时，尾后迭代器总是失效。


> 建议: 管理迭代器。由于迭代器增删元素的代码可能会使迭代器失效，因此必须保证每次改变容器的操作之后都正确的重新定位迭代器。这个建议对 vector/ string/ deque 尤为重要。








#### 编写改变容器的循环程序

如果循环中调用 insert 或 erase，那么更新迭代器很容易。这些操作都返回迭代器，我们可以用来更新:

```
// 傻瓜循环，删除偶数元素，复制每个奇数元素
#include<iostream>
#include<vector>
using namespace std;

//在循环中改变容器
int main(){
    vector<int> vi={0,1,2,3,4,5};
    auto iter=vi.begin();  //调用begin 而不是 cbegin，因为我们要改变vi
    // 删除偶数元素，复制每个奇数元素
    while(iter != vi.end()) {
        if( *iter %2){ //如果是奇数
            iter = vi.insert(iter, *iter); //复制当前元素：在iter所指位置之前插入元素 *iter，返回新插入的元素位置
            iter+=2; //向前移动2，跳过新插入的元素和原 iter指向的元素
        }else{
            iter = vi.erase(iter); // 删除偶数元素：返回被删元素的下一个位置
        }
    }

    //打印
    for(auto i: vi)
        cout << i << " ";
    cout << endl; 
    
    return 0;
}

$ g++ b15_modify_ctn_in_loop.cpp 
$ ./a.out 
1 1 3 3 5 5 
```

该程序删除 vector 中的偶数元素，并复制每个奇数元素。我们调用 insert 和 erase 后都更新迭代器，因为两者都会使迭代器失效。

- erase(iter) 返回被删元素的下一个位置
- insert(iter, val) 在iter指定位置之前插入元素 val, 并指向新添加的元素。所以上文需要递增2次才能到下一个元素。










#### 不要保存 end 返回的迭代器

- 当我们增删vector或 string 的元素后，或在 deque 首尾元素之外任意位置增删元素后，原来end返回的迭代器总是失效。
- 因此，增删元素的循环必须反复调用end。而不能一直使用循环前保存的end。

例: 一个循环，处理每个元素，并在其后新增一个元素。我们希望跳过新增的元素。

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> v={0,1,2,3};
    auto begin=v.begin(), 
        end=v.end(); //保存尾后迭代器是一个坏主意

    // while(begin != end){ //Segmentation fault (core dumped)
    while(begin != v.end()){
        //做一些处理
        *begin = - *begin; // 改变符号
        // 插入新值，对begin 重新赋值，否则的话它就会失效
        ++begin;  //向前移动begin()，因为我们想在此元素后插入元素
        begin = v.insert(begin, 100); //插入新值
        ++begin; //向前移动，跳过新插入的值
    }

    // 打印结果
    for(auto i: v)
        cout << i << " ";
    cout << endl;
}

$ g++ b16_end_refresh.cpp 
$ ./a.out 
0 100 -1 100 -2 100 -3 100
```

- 使用循环前保存的 end，会导致报错 `Segmentation fault (core dumped)`
- 这是因为新增元素会使end迭代器失效，这个迭代器不在指向v的任何元素或尾后位置。
- 必须在每次插入操作后重新调用end()，而不能使用循环前保存的尾后迭代器。

> Tip: 如果在一个循环中插入/删除 deque、string 或 vector 中的元素，不要缓存 end 返回的迭代器。














## 9.4 vector 对象是如何增长的

vector 或 string 需要连续空间存储，保证随机访问的速度。

如果有新增元素，则请求多一些空间，以便减少重新分配新内存空间的频率。





#### 管理容量的成员函数

- capacity 告诉我们容器在不扩张内存空间的情况下可以容纳多少个元素；
- reserve 操作允许我们通知容器它应该准备保存多少个元素


- 表9.10 容器大小的管理
    * shrink_to_fit 只适用于 vector/string/deque
    * capacity 和 reserve 只适用于 vector 和 string
    * c.shrink_to_fit() 请将 capacity() 减少为与 size()相同大小
    * c.capaticy()  不重新分配内存空间的话，c可以保存多少元素
    * c.reserve(n)  分配至少能容纳 n 个元素的内存空间

> Note: reserve 并不改变容器中元素的数量，它仅影响 vector 预先分配多大的内存空间。


- 只有当需要的内存空间超过当前容量时，reserve调用才会改变 vector 的容量。如果需求大于当前容量，reserve 至少分配与需求一样大的空间（可能更大）
- 如果需求小于等于当前容量，reserve 什么也不做。但需求小于当前容量时，容器不会退回内存空间。因此，调用 reserve 后，capacity 将会大于或等于传递给 reserve 的参数。
- 所以，调用 reserve 永远不会减少容器占用的内存空间。
    * 类似的，resize(9.3.5，P314)只改变容器中元素的数目，而不是容器的容量。不能使用 resize 减少容器预留的内存空间。
- 新标准中， shrink_to_fit 可以要求 deque、vector 或 string 退回不需要的内存空间。但是具体的实现可以选择忽略该请求，也就是说不能保证一定退回内存空间。




#### capacity 和 size

- size 是已经保存的元素个数
- capacity 是不分配新的内存空间的情况下，它最多可以保存多少个元素。

例：展示 size 和 capacity 的相互作用

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> ivec;
    //size 应该是0； capacity 的值依赖于具体实现
    cout << " ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;
        
    // 添加24个元素
    for(vector<int>::size_type ix=0; ix!=24; ++ix){
        ivec.push_back(ix);
    }
    // size 应该是24； capacity 的值依赖于具体实现
    cout << " ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;
    return 0;
}

$ g++ b17_size_capacity.cpp 
$ ./a.out 
 ivec size:0 capacity:0
 ivec size:24 capacity:32
```


请求分配更多空间
```
    ivec.reserve(50);
    // size 应该是24； capacity 的值依赖于具体实现，应该大于等于50
    cout << " ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;

输出:
ivec size:24 capacity:50
```


添加元素，用完剩余空间
```
    while( ivec.size() != ivec.capacity() )
        ivec.push_back(0);
    // capacity 应该未改变
    cout << "4 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;

输出:
4 ivec size:50 capacity:50
```


再添加1个元素，vector 就不得不重新分配内存空间了
```
    ivec.push_back(1);
    // capacity 应该未改变
    cout << "5 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;

输出:
5 ivec size:51 capacity:100
```

这里看，似乎每次请求空间，capacity 都是翻倍。

可以采用 shrink_to_fit 要求 vector 退回多余的空间给系统：
```
    ivec.shrink_to_fit();
    cout << "6 ivec size:" << ivec.size()
         << " capacity:" << ivec.capacity() << endl;

输出:
6 ivec size:51 capacity:51
```

> note: 每个 vector 实现都可以选择自己的内存分配策略。但必须遵守一条原则：只有当迫不得已时才可以分配新的内存空间。


- 只有在执行 insert 操作时 size 和 capacity 相等，或者调用 resize 或 reserve 是给定的大小超过当前 capacity，vector 才可能重新分配内存空间。
    * 分配多少取决于实现。
    * 不同实现都最少一个原则：确保用 push_back 向vector 添加元素的操作有高效率。
    * 技术上来说，就是在一个初始为空的vector上调用n次push_back来创建一个n个元素的vector，所花费的时间不能超过n的常数倍。









## 9.5 额外的 string 操作

顺序容器共同的操作之外，string类还有一些独有的操作：

- 大多是提供给 string类和C风格字符数组之间互转
- 部分允许用下标代替迭代器


因为这些函数使用了重复的模板，读着心烦。

- 作者建议该部分可以略读：了解 string 支持哪些类型的操作，需要了再回头研读。
- //todo jump 太繁琐


### 9.5.1 构造 string 的其他方法

除了(P76, 3.2.1) 介绍过的string 构造函数，及与其他顺序容器相同的构造函数(P299, 9.3)，string 还有3个构造函数。

- 表 9.11 构造 string 的其他方法
    * n、len2 和 pos2 都是无符号值
    * string s(cp, n)  s是cp指向的数组中前n个字符的拷贝。此数组至少应该包含n个字符
    * string s(s2, pos2)  s是 string s2 从下标 pos2 开始的字符的拷贝。若 pos2>s2.size()，构造函数的行为未定义
    * string s(s2, pos2, len2)  s是string s2 从下标pos2开始len2个字符的拷贝。若pos2>s2.size()，构造函数的行为未定义。不管len2的值是多少，构造函数最多拷贝 s2.size() - pos2 个字符。


#### substr 操作

s.substr(pos, n)  返回一个string，包含s中从pos开始的n个字符的拷贝。pos的默认值是0，n的默认值是 s.size()-pos, 即从pos开始的所有字符。





### 9.5.2 改变 string 的其他操作

string 类型支持顺序容器的赋值运算符以及 assign、insert和erase 操作(P302,9.2.5;  P306,9.3.1;  P311,9.3.3)。

- string 还定义了额外的 insert 和 erase 版本。除了接收迭代器的，还可以接收下标。
- 下标给出开始删除的位置，或者 insert 到给定值之前的位置。

```
#include<iostream>
using namespace std;

int main(){
    string s="hello";
    cout << "1 " << s << endl;
    
    s.insert(s.size(), 5, '!'); //在s的末尾添加5个感叹号
    cout << "2 " << s << endl;

    s.erase(s.size()-5, 5);  //从s删除最后5个字符
    cout << "3 " << s << endl;

    return 0;
}

$ g++ c1_string_insert.cpp 
$ ./a.out 
1 hello
2 hello!!!!!
3 hello
```

标准库string类型还提供了接受C风格字符数组的 insert 和 assign 版本。

```
#include<iostream>
using namespace std;

// 接受C风格的字符串数组
int main(){
    string s="this is a book";
    cout << "1 " << s << endl;

    const char *cp="hello, world!";
    s.assign(cp, 7); // 获取cp前7个字符，覆盖到s上
    cout << "2 " << s << endl;

    // 插入：要插入的位置，指向新字符串的指针位置
    s.insert(s.size(), cp+7); //结尾不存在的字符之前插入字符串 cp+7 的拷贝
    cout << "3 " << s << endl;

    //插入开头
    string s2="NEW BOOK.";
    s.insert(0, s2); //在0位置之前插入字符串s2的拷贝
    cout << "4 " << s << endl;

    // 在s开头之前，插入s2[0]开始到 s2.size()-1个字符
    string s3="a fox";
    s.insert(0, s3, 0, s3.size()-1 );
    cout << " s3.size()=" << s3.size() << endl;
    cout << "5 " << s << endl;
}

$ g++ c2_string_insert_C.cpp 
$ ./a.out 
1 this is a book
2 hello, 
3 hello, world!
4 NEW BOOK.hello, world!
 s3.size()=5
5 a foNEW BOOK.hello, world!
```








#### append 和 replace 函数

string 类定义了两个额外的成员函数： append 和 replace，这两个函数可以改变 string 的内容。

- append 是在 string 末尾插入操作的一种简写:

```
    string s1("C++ book"), s2=s1;
    s1.insert(s1.size(), " 5th edition");; //在末尾插入
    s2.append(" 5th Edi");//简写
```


- replace 是调用 erase 和 insert 的一种简写形式:

```
    string s1="C++ book, 4th", s2=s1;
    cout << "s1.size()=" << s1.size() << endl;
    //把4th替换为 5th
    //方法1:
    s1.erase(10, 3);
    cout << "s1=" << s1 << endl;
    s1.insert(10, "5th");
    cout << "s1=" << s1 << endl;

    //方法2:  简化方法
    cout << "\ns2=" << s2 << endl;
    s2.replace(10, 2, "5th");
    cout << "s2=" << s2 << endl;
```

上例子中，插入的字符恰好与删除的文本等长，这不是必须的。

```
    string s1="c++ book, 4th";
    cout << "s1=" << s1 << endl;
    s1.replace(10, 2, "5th Edition");
    cout << "s1=" << s1 << endl; //c++ book, 5th Editionh
```
注意，我们删除了2个字符(5t)，然后插入了11个字符，最后没有删除的h还在。



- 表9.13 修改 string 的操作
    * s.insert(pos, args)  在 pos 之前插入 args 指定的字符。pos 可以是一个下标或一个迭代器。接受下标的版本返回一个指向s的引用；接受迭代器的版本返回指向第一个插入字符的迭代器。
    * s.erase(pos, len)  删除从位置pos开始的len个字符。如果len被省略，则删除从 pos 开始直到 s 末尾的所有字符。返回一个指向s的引用。
    * s.assign(args)  将s中的字符替换为args指定的字符，返回一个指向s的引用。
    * s.append(args)  将args追加到s。返回一个指向s的引用
    * s.replace(range, args) 删除s中范围range内的字符，替换为args 指向的字符。range或者一个下标和一个长度，或者是一对指向s的迭代器。返回一个指向s的引用。
    * args 可以是下列形式之一； append 和 assign 可以使用所有形式
    * str不能与s相同，迭代器b和e不能指向s
        * str  字符串str
        * str,pos,len  str中从pos开始最多len个字
        * cp, len  从cp指向的字符数组的前(最多)len个字符
        * cp  (就是C风格的字符串) cp指向的以空字符结尾的字符数组
        * n,c   n个字符c
        * b,e  迭代器b和e指定范围内的字符
        * 初始化列表  花括号包围，以逗号分割的字符列表
    * replace 和 insert 所允许的args 形式依赖于 range 和 pos 是如何指定的: P324




#### 改变 string 的多种重载函数

表 9.13 给出了 append/assign/insert/replace 函数的多个重载版本。

- assign 和 append 函数指定要替换string 的哪个部分；
    * assign 总是替换string中的所有内容
    * append 总是把新字符追加到string末尾
- replace 函数提供了两种指定删除元素范围的方式：
    * 位置 + 长度
    * 迭代器
- insert 两种方式指定插入点，新元素插入到给定位置之前。
    * 下标
    * 迭代器


可以有好几个方法指定要添加到string 中的字符。

新字符可以来自另一个string，来自于一个字符指针(指向的C风格字符串)，来自于一个花括号包围的字符列表，或者一个字符加一个计数值。

当字符来自string或C风格字符串时，可以传递额外参数控制拷贝部分还是全部字符。

- 并不是每个函数都支持所有形式的参数。
    * insert 不支持下标和初始化列表参数。见下文反例1
    * 如果用迭代器指定插入点，就不能用字符指针指定新字符的来源。可以使用下标+C风格字符，或迭代器+单个字符。

```
    //反例1: insert 使用下标+初始化列表参数
    string s1="hi";
    s1.insert(2, {", world!"});
    cout << "1 " << s1 << endl;


    //例子2: 迭代器 + c风格字符串，报错
    string s2="hello, ";
    char cp[]="this is g++";
    //s2.insert(s2.size(), cp); //找不到对应的重载函数
    s2.insert(s2.end(), *cp); //可以插入单个字符
    cout << "2 " << s2 << endl;

```




### 9.5.3 string 搜索操作

string 类提供了6个不同的搜索函数，每个函数有4个重载版本。

返回值都是 string::size_type 值，表示匹配发生位置的下标。
    如果搜索失败，则返回一个名为 string::npos 的 static 成员(见7.6， P268)。
        标准库把 npos 定义为一个 const string::size_type 类型，并初始化为值-1.
        由于 npos 是一个unsigned类型，次初始值意味着 npos 等于任何 string 最大的可能大小(2.1.2, P32)

> 警告：string 搜索结果是一个 string::size_type 类型，是 unsigned 类型。因此用 int 或其他带符号类型保存这些值不好(2.1.2, P33)


- find 简单搜索，查找参数指定的字符串。找到，则返回第一个匹配的下标，否则返回 npos.
    * 搜索是大小写敏感的。

```
    string name("this is a cpp book");
    auto pos1= name.find("is");
    cout << pos1 << endl; //2
    
    //搜不到时
    auto pos2= name.find("python");
    cout << pos2 << endl; //18446744073709551615 //任何string可能的最大大小

    //怎么判断未找到？
    if( pos2== string::npos ){
        cout << "not found!" << endl;
    }
```


- 更复杂的问题，查找与给定字符串中任何一个匹配的位置:

```
    string numbers("0123456789"), addr("6375b1");
    auto pos=addr.find_first_of(numbers);
    cout << pos << endl;  //0  addr中第0个字符‘6’首次出现在 numbers中
```


- 如果要搜索不在第一个参数中的字符，调用方法 find_first_not_of: 

```
    string numbers("0123456789"), addr("0375b1");
    auto pos2=addr.find_first_not_of(numbers); //addr 中第4个字符‘b’不在 numbers中
    cout << pos2 << endl;  //4
```

- 表9.14 string 搜索操作
    * 搜索操作返回指定字符出现的下标，如果未找到则返回 string::npos(最大string的长度)
        * s.find(args)  查找s中args第一次出现的位置
        * s.rfind(args);  查找s中args最后一次出现的位置
        * s.find_first_of(args);  在s中查找args中任何一个字符第一次出现的位置
        * s.find_last_of(args);  在s中查找args中任何一个字符最后一次出现的位置
        * s.find_first_not_of(args);  在s中查找第一个不在args中的字符
        * s.find_last_not_of(args); 在s中查找最后一个不在 args 中的字符
    * args 必须是以下形式之一
        * c,pos  从s中位置pos开始查找字符c。pos默认为0
        * s2,pos  从s中位置pos开始查找字符串s2。pos默认值为0
        * cp,pos  从s中位置pos开始查找指针cp指向的以空字符结尾的C风格字符串。pos默认为0
        * cp,pos,n  从s中位置pos开始查找指针cp指向的数组前n个字符。pos和n无默认值



#### 指定从哪里开始搜索 `s.find(s2, pos)`

从s的第pos个字符开始查找字符s2的位置。我们可以结合循环，给出字符s中s2的所有下标。

```
void demo4(){
    string::size_type pos=0;
    string s1="this is a book, which is about C++", s2="is";
    while( (pos = s1.find(s2, pos)) != string::npos ){
        cout << "found s2 at index:" << pos 
            << " element is: " << s1.substr(pos) << endl;
        pos++;
    }
}


输出:
found s2 at index:2 element is: is is a book, which is about C++
found s2 at index:5 element is: is a book, which is about C++
found s2 at index:22 element is: is about C++
```

注意：如果忽略在while中的pos++，则会陷入死循环！






#### 逆向搜索 `s.rfind(s2)`

提供从右向左搜索。

类似的，find_last 函数功能与 find_first 类似，只是返回最后一个匹配 或 不匹配。
- find_last_of()
- find_last_not_of() 

每个操作都接受一个可选的第二个参数，用来指定从什么位置开始搜索。






### 9.5.4 compare 函数

标准库 string 类型还提供了一组 compare 函数，与C标准库的 strcmp 函数(3.5.4, P109)很相似。
    * 类似 strcmp， 根据s是等于、大于还是小于参数字符串，s.compare 返回0，正数和负数。

compare 有6个版本。string vs string， 或者 string vs C风格字符串。都可以完整比较或比较一部分。

- 表9.15 s.compare 的几种参数形式
    * s2   //比较 s 和 s2
    * pos1, n1, s2  //将s中从pos1开始的n1个字符与s2进行比较
    * pos1, n1, s2, pos2, n2 //将s中从pos1开始的n1个字符与s2中从pos2开始的n2个字符进行比较
    * cp  比较s与C风格字符串cp
    * pos1,n1, cp 
    * pos1,n1, cp,n2




### 9.5.5 数值转换

一个数字的字符表示不同于其数值。
- 数值 15 如果保存为16位的short类型，其二进制位模式为 `00000000 00001111`
- 数值15表示成string，则其二进制形式为: `00110001 00110101`, 第一个字节表示字符 '1'，第二个字节表示字符'5'；

新标准引入了多个函数，可以实现数值数据与标准库string之间的转换:

```
    int i=15;
    string s=to_string(i); //整数 to string

    double d= stod(s); //字符串s转换为浮点数
```



字符串转为数字，第一个字符必须是数字可能出现的字符:
```
    string s2="pi = 3.1415926"; //直接转数字，运行时报错:  what():  stod  Aborted (core dumped)
    double d2=stod(s2.substr(s2.find_first_of("+-.0123456789")));
```

- 字符可以用0x或0X开头表示16进制数；
- 字符里根据需要，可以.开头，可以包含e或E表示指数部分。
- 对于字符串转为整数的函数，根据基数不同，可以包含大于9的字母字符。


> Note: 如果string不能转为一个数值，则这些函数抛出异常 'std::invalid_argument'(P5.6, P173)。如果转换得到的数值无法用任何类型来表示，则抛出一个 out_of_range 异常。


- 表9.16 string 和数值之间的转换
    * to_string(val)  一组重载函数，返回数值 val 的 string 表示。val 可以是任何算术类型(2.1.1节，P30)。对每个浮点类型和int或更大的整型，都有相应版本的重载。与往常一样，小整型会被提升(4.11.1, P142)
    * stoi(s, p, b)  返回s的起始子串(表示整数内容)的数值，返回类型是 int, long, unsigned long, long long, unsigned long long。b表示转换所用的基数，默认值是10。p是size_t指针，用来保存s中第一个非数值字符的下标，p默认为0，即，函数不保存下标。
    * stol(s,p,b)
    * stoul(s,p,b)
    * stoll(s,p,b)
    * stoull(s,p,b)
    * stof(s,p)   返回s的起始子串（表示浮点数内容）的数值，返回值类型分别是 float，double 或者 long double。参数p的作用域整数转换函数中的一样。
    * stod(s,p)
    * stold(s,p)









## 9.6 容器适配器

除了顺序容器外，标准库还定义了三个顺序容器适配器： stack, queue 和 priority_queue。

- 适配器(adaptor) 是标准库中的一个通用概念。容器、迭代器和函数都有适配器。
    * 本质上，适配器是一种机制，能使某种事物的行为看起来像另外一种事物一样。
    * 一个适配器接受一种已有的容器类型，使其行为看起来像一种不同的类型
        * 例如：stack适配器接受一个顺序容器(除 array 或  forward_list 外)，并使其操作起来像一个 stack 一样。

- 表 9.17 所有容器适配器都支持的操作和类型
    * size_type  一种类型，足以保存当前类型的最大对象的大小
    * value_type  元素类型
    * container_type 实现适配器的底层容器类型
    * A a;  创建一个名为a的空适配器
    * A a(c); 创建一个名为a的适配器，带有容器c的一个拷贝
    * 关系运算符  每个适配器都支持所有关系运算符: `==, !=, <, <=, >, >=`，这些运算符返回底层容器的比较结果
    * a.empty() 若a包含任何元素，返回false，否则返回true
    * a.size() 返回a中的元素数目
    * swap(a,b)  交换a和b的内容，a和b必须有相同类型，包括底层容器类型也必须相同
    * a.swap(b)




#### 定义一个适配器

每个适配器都有2个构造函数：
- 默认构造函数创建一个空对象
- 接收一个容器的构造函数拷贝该容器来初始化适配器。
    
例如 deq 是一个 `deque<int>`，我们可以用 deq 来初始化一个新的 stack: 

`stack<int> stk(deq); //从元素从deq拷贝元素到stk`


```
#include<iostream>
#include<deque>
#include<stack>
using namespace std;

void demo1(){
    //定义一个容器
    deque<int> deq={1,2,30,40};
    for(auto i: deq){
        cout << i << endl;
    }
    cout << endl;

    // 栈：先进后出
    stack<int> stk(deq); //从deq拷贝元素到stk
    while(!stk.empty()){
        int val=stk.top(); //获取顶端的值
        stk.pop(); //删掉顶端的值
        cout << val << endl;
    }
}

int main(){
    demo1();
}


$ g++ c8_adapter.cpp 
$ ./a.out 
1
2
30
40

40
30
2
1
```




默认情况下，stack 和 queue 是基于deque实现的，priority_queue 是在 vector 之上实现的。
我们可以在创建一个适配器时将一个命名的顺序容器作为第二个类型参数，来重载默认容器类型。


```
#include<iostream>
#include<stack>
#include<vector>
#include<string>

using namespace std;

// 适配器的第二个参数：类型参数

int main(){
    vector<string> svec={"this", "is", "a", "book"};
    //在 vector 上实现的空栈
    stack<string, vector<string>> str_stk;

    // str_stk2 在 vector 上实现，初始化时保存 svec 的拷贝
    stack<string, vector<string>> str_stk2(svec);

    //打印栈: 先进的后出
    while(!str_stk2.empty()){
        string val=str_stk2.top(); //获取顶端的值
        str_stk2.pop(); //删掉顶端的值
        cout << val << endl;
    }

    return 0;
}


$ g++ c9_adapter_2ndPara.cpp 
$ ./a.out 
book
a
is
this
```

- 对于一个给定的适配器，可以使用哪些容器是有限制的。
    * 所有适配器都要求容器具有添加和删除元素的能力。
        * 因此，适配器不能构造在array之上。
        * 也不能用 forward_list 来构造适配器，因为所有适配器都要求容器具有添加、删除、访问尾元素的能力。
    * stack 只要求 push_back， pop_back 和 back 操作，因此可用除 array 和 forward_list 之外的任何容器来构造 stack。
    * queue 适配器要求 back/ push_back/ front /push_front，
        * 因此它可以构造于 list 或 deque 之上
        * 不能基于 vector 构造。
    * priority_queue 除了 front/ push_back /pop_back 操作之外还要求随机访问能力，
        * 因此它可以构造于 vector 或 deque 之上，
        * 不能基于 list 构造




#### 栈适配器

演示把元素压入栈，再打印出来。最先进的是0，最后出来。

```
#include<iostream>
#include<stack>
using namespace std;

//栈 适配器
int main(){
    stack<int> intStack; //空栈
    // 填满栈
    for(size_t ix=0; ix!=5; ++ix){
        intStack.push(ix); //保存0-4共5个整数
    }

    //打印结果
    while(!intStack.empty()){
        int value=intStack.top(); //获取顶部元素
        intStack.pop();  //弹出栈顶元素，没有返回值
        cout << value << " ";
    }
    cout << endl;

    return 0;
}


$ g++ c10_adapter_stack.cpp 
$ ./a.out 
4 3 2 1 0
```



- 表9.18 表9.17未列出的栈操作
    * 栈默认基于 deque 实现，也可以在list或vector之上实现
    * s.pop()   删除栈顶元素，但不返回该元素值
    * s.push(item)  创建一个新元素压入栈顶，该元素通过拷贝或移动item而来，或者由args构造
    * s.emplace(args)
    * s.top()  返回栈顶元素，但不将元素弹出栈


每个容器适配器都基于底层容器类型的操作定义了自己的特殊操作。我们只能使用适配器的操作，而不能使用底层容器类型的操作。

* intStack.push(ix);  //intStack 保存整数ix
* 虽然 stack 基于 deque实现，但是不能调用deque的push_back方法，而必须调用stack自己的方法 push。



#### 队列适配器

queue 和 priority_queue 适配器定义在 queue 头文件中。

- 表9.19 表9.17未列出的 queue 和 priority_queue 操作
    * queue 默认基于 deque 实现，priority_queue 默认基于 vecotr 实现
    * queue 也可以用 list 或 vector 实现，priority_queue也可以用 deque 实现
    * q.pop()  返回队列首元素或 priority_queue优先级最高的元素，但不删除该元素
    * q.front()  返回首元素或尾元素，但不删除该元素
    * q.back()  只适用于queue。
    * q.top()  返回最高优先级的元素，但不删除该元素。只适用于 priority_queue
    * q.push(item)  在queue末尾或 priority_queue 中恰当的位置创建一个元素，其值为item，或者由args构造
    * q.emplace(args)


- queue 先进先出的存储和访问策略。队尾添加，对首离开。
    * 就像排队买票场景一样。
- priority_queue 允许为队列中的元素建立优先级。新来的元素排在所有优先级比它低的已有元素之前。
    * 饭店就餐按照预约时间，而不是来的时间安排座位，时间为优先级。
    * 默认，标准库使用`<`运算符来确定相对优先级。(11.2.2, P378)学习如何重载该默认设置。













## 小结

P332


- 所有容器（除array外）都提供高效的动态内存管理。
    * vector 和 string 提供更细致的内存管理控制：通过 reserve 和 capacity 成员函数来实现的
- 容器的元素的排序或搜索，并不是容器类型定义的，而是由标准库算法实现的。见第10章。
- 添加和删除元素，可能导致指向容器元素的迭代器、指针或引用失效。
    * 使迭代器失效的操作，如insert 和 erase 会返回新的迭代器，帮助用户维护容器中的位置。
    * 循环中改变了容器的大小，要特别小心其中迭代器、指针和引用的使用。



