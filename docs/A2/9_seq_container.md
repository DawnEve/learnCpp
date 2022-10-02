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
a2={0};  //错误: 不能将一个花括号列表赋值给array  //注: 我认为作者写错了，这里不报错，是把a2元素归零。
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


> 警告：将元素插入到 vector、deque和string中的任何位置都是合法的。也是耗时的。





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









> 334/384









### 9.3.2 访问元素

### 9.3.3 删除元素

### 9.3.4 特殊的 forward_list 操作

### 9.3.5 改变容器的大小

### 9.3.6 改变操作可能使迭代器失效
























## 9.4 vector 对象是如何增长的



















## 9.5 额外的 string 操作





















## 9.6 容器适配器



















## 小结















