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


> P324/864













## 9.3 顺序容器操作




















## 9.4 vector 对象是如何增长的



















## 9.5 额外的 string 操作





















## 9.6 容器适配器



















## 小结















