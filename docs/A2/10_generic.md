# 第10 章 泛型算法

标准库容器定义的操作很少。

标准库提供了一组算法，他们是通用的（generic，或称泛型的）：它们可用于不同类型的容器和不同类型的元素。

主要内容: 泛型算法和迭代器的更多细节



- 查找、替换、删除一个特定的值、排序等。
- 泛型算法(generic algorithm)
    * 算法：实现了一些经典算法的公共接口，如排序和搜索。
    * 泛型：它们可用于不同类型的元素和多种容器类型。








## 10.1 概述

- 算法大多在 algorithm 头文件中。
- 标准库还在 numeric 头文件中定义了一组数值泛型算法。


- 这些算法不直接操作容器，而是遍历由2个迭代器指定的一个元素范围(9.2.1, P296)。

例1: vector中是否包含某个值，使用标准库的算法 find

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> ivec={1,2,5,9,10,15};
    int val=10;
    auto result=find(ivec.begin(), ivec.end(), val);
    cout << "The value " << val << 
        (result==ivec.end() ? " is NOT in vector": " is in vector") << endl;
    return 0;
}

$ g++ a1_find_vector.cpp 
$ ./a.out 
The value 10 is in vector
```

由于find操作的是迭代器，所以可以在任何容器中查找值。


例2: 在string的list中用find查找一个值。
```
#include<iostream>
#include<list>
#include<algorithm>
using namespace std;

int main(){
    list<string> lst={"this", "is", "a value"};
    string val="a value2";
    auto result=find(lst.cbegin(), lst.cend(), val);
    cout << "The value '" << val << 
        (result==lst.cend() ? "' is NOT in list": "' is in list") << endl;
    return 0;
}

$ g++ a2_find_list.cpp 
$ ./a.out 
The value 'a value2' is NOT in list
```


例3: 类似的，由于指针就像内置数组上的迭代器一样，可以用 find 在数组中查找值:
```
#include<iostream>
#include<algorithm>
using namespace std;

//内置数组上使用 find 查找值
int main(){
    int arr[]={1,2,3,4,5}, len=sizeof(arr)/sizeof(int);
    printf("begin(arr):%p, arr:%p\n", begin(arr), arr); //首元素地址
    printf("end(arr):%p, arr+len:%p\n", end(arr), arr+len); //尾后位置地址
    // 一个给定的值
    int val=30;
    int* result=find(begin(arr), end(arr), val);
    printf("result:%p, arr+len:%p\n", result, arr+len);
    cout << "The value " << val << 
        (result==arr+ len ? " is NOT in arr": " is in arr") << endl;
    return 0;
}


$ g++ a3_find_arr.cpp 
$ ./a.out 
begin(arr):0x7ffeccad5940, arr:0x7ffeccad5940
end(arr):0x7ffeccad5954, arr+len:0x7ffeccad5954
result:0x7ffeccad5954, arr+len:0x7ffeccad5954
The value 30 is NOT in arr
```




#### 算法如何工作

find 不依赖容器的类型（甚至无需理会保存元素的是不是容器）


#### 迭代器令算法不依赖于容器，...

除了相等的判断，其他都是迭代器操作：

- *iter 获取值
- iter++ 获取下一个迭代器
- 找到了，则返回指向该值的迭代器；找不到，则返回指向尾后位置的迭代器。



#### ...，但算法依赖于元素类型的操作

find 使用 == 来进行相等的比较。

例: 类似于 find 的操作 count，接受一对迭代器和一个值，返回该值出现的次数。

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    vector<int> ivec={1,2,2,2,3,3,4};
    for(int i=1; i<6; i++){
        auto rs=count(ivec.cbegin(), ivec.cend(), i);
        cout << i << ": " << rs << endl;
    }

    return 0;
}


$ g++ a4_count_vector.cpp 
$ ./a.out 
1: 1
2: 3
3: 2
4: 1
5: 0
```

- 关键概念：算法永远不会执行容器的操作！
    * 算法执行在迭代器上，所以永远不会改变容器的大小。算法可以改变容器中元素的值，但是不会直接添加或者删除元素。
    * 但是算法可以操作一个迭代器，迭代器完成 向容器添加元素的(insert) 操作，但算法自身永远不会做这样的操作。







## 10.2 初始泛型算法

标准库提供了100多个算法。有一致的结构。

- 除了少数例外，都是对一个输入范围(一对迭代器)的元素进行操作。
- 使用范围内元素的方式不同：是否读取元素、改变元素或者重排元素。


### 10.2.1 只读算法

只读取，比如find和count。

例: 另一个是 accumulate，定义在 numeric 头文件中，前2个参数是迭代器，第三个参数是求和的初始值。
```
#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

int main(){
    vector<int> ivec={1,3,5,7};
    // 对vec中的元素求和，和的初始值是0
    int sum=accumulate(ivec.begin(), ivec.end(), 0);
    cout << "sum="  << sum << endl;
    return 0;
}

$ g++ a5_accumulate_vector.cpp 
$ ./a.out 
sum=16
```

> Note: accumulate 的第三个参数决定了使用哪个加法运算符以及返回值的类型。




#### 算法和元素类型

例: 由于string 定义了+运算符，所以可以将vector中的string连起来。
```
#include<iostream>
#include<numeric>
#include<vector>

using namespace std;

int main(){
    vector<string> svec={"this", "is", "a", "book"};
    //输出
    for(auto i: svec)
        cout << i << endl;
    // 连起来
    string sum2=accumulate(svec.begin(), svec.end(), string(""));
    cout << "sum2=" << sum2 << endl;
    return 0;
}

$ g++ a6_accumulate_vector_string.cpp 
$ ./a.out 
this
is
a
book
sum2=thisisabook
```

字符串字面量当第三个参数报错: const char* 没有定义+运算符：
```
string sum2=accumulate(svec.begin(), svec.end(), "");
//error: cannot convert ‘std::__cxx11::basic_string<char>’ to ‘const char*’ in assignment
```


> 最佳实践: 对于只读而不改变元素的算法，通常最好使用 cbegin() 和 cend() (9.2.3, P298)。但是如果想使用算法返回的迭代器改变元素的值，则使用 begin()和 end().





#### 操作2个序列的算法

- equal 也是只读算法，确定2个序列是否保存相同的值。按元素逐个比较，都相等则返回true，否则 false。
- 接收3个迭代器，前两个与之前一样，第三个是指向第二个序列的首元素

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<string> s1={"this", "is", "a", "book"}, s2={"this", "is", "a", "book2"};
    //s2=s1;
    bool rs=equal(s1.cbegin(), s1.cend(), s2.cbegin());
    cout << rs << endl;
    return 0;
}

$ g++ a7_equal_string.cpp 
$ ./a.out 
0
# 把注释去掉 s2=s1; 则输出 1
```

- 因为 equal 是通过迭代器实现的，所以可以通过 equal 比较不同类型容器中的元素。
    * 且元素类型不一定一样，只要能用==比较即可。
    * 比如例2中 `vector<string> s1`，`list<const char*> s2`;
- 但是，equal 基于一个重要的假设：第二个序列至少与第一个序列一样长，此算法要处理第一个序列中的每个元素。
    * 如果第二个序列更长，且之前的元素和序列1一样呢？看例2中的 s1 vs s4，返回值是相等?!

例2: 不同容器类型的元素的比较。
```
#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

int main(){
    vector<string> s1={"this", "is"};
    list<const char*> s2={"this", "is"}, s3={"this", "is3"}, s4={"this", "is", "a"};
    cout << equal(s1.cbegin(), s1.cend(), s2.cbegin()) << endl; //1
    cout << equal(s1.cbegin(), s1.cend(), s3.cbegin()) << endl; //0
    cout << equal(s1.cbegin(), s1.cend(), s4.cbegin()) << endl; //1
    return 0;
}
```

> 警告: 那些只接受一个单一迭代器表示第二个序列的算法，都假定第二个序列至少与第一个序列一样长。






### 10.2.2 写容器元素的算法

- 记住: 算法不会执行容器操作，因此他们自身不可能改变容器的大小。
- 一些算法会写入元素，但最多写入与给定序列一样多的元素。

例: fill 接受一对迭代器表示范围，还接受一个值作为参数3，fill把参数3赋值给序列中的每个元素。

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> ivec={0,1,2,3,4,5};
    //每个元素重置为0
    fill(ivec.begin(), ivec.end(), 0);
    //输出
    for(auto ele: ivec){
        cout << ele << endl;
    }
    printf("\n");

    //子序列重置为5
    fill(ivec.begin(), ivec.begin()+ivec.size()/2, 5);
    //输出
    for(auto ele: ivec){
        cout << ele << endl;
    }

    return 0;
}
```


> 关键概念: 迭代器参数 P340








#### 算法不检查写操作

- `fill_n(dest, n, value)` 从参数1指定的迭代器开始，共n位置，都填充为值value。
- dest指向一个元素，比如vec.begin()，从dest开始的序列至少包含n个元素。
- 如果参数2超过 vec.size()，则未定义 UB。

> 警告: 向目的位置迭代器写入数据的算法假定目的位置足够大，能容纳要写入的元素。

```
#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> vec;
    cout << vec.size() << endl;

    vec={1,2,3};
    cout << vec.size() << endl;
    fill_n(vec.begin()+1, 2, 100); //从下标1开始的2个位置，填充值100
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl;

    return 0;
}

$ g++ a10_fill_n.cpp 
$ ./a.out 
0
3
1 100 100
```


#### 介绍 back_inserter

插入迭代器(insert iterator) 是一种向容器中添加元素的迭代器。

- back_inserter 函数定义在头文件 iterator 中。
- 接收一个指向容器的引用，返回一个该容器绑定的插入迭代器。
    - 通过此迭代器赋值时，赋值运算符会调用 push_back 将一个具有给定值的元素添加到容器中。

```
#include<iostream>
#include<iterator>
#include<vector>
using namespace std;

int main(){
    vector<int> vec={1,2,3};
    auto it=back_inserter(vec); //返回迭代器
    *it=42; //调用 push_back，把等号右侧的元素添加到原容器中
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl;

    return 0;
}

$ g++ a11_back_inserter.cpp 
$ ./a.out 
1 2 3 42
```


- 常常使用 back_inserter 来创建一个迭代器，作为算法的目的位置来使用。
    * `fill_n( back_inserter(vec), 3, 100)`
    * 每步的迭代中，fill_n向给定序列的一个元素赋值，由于参数1是 back_inserter 返回的是迭代器，因此每次赋值都会在 vec 上调用 push_back。
    * 最终在 vec 末尾添加了3个元素，每个元素都是100.


```
#include<iostream>
#include<iterator>
#include<vector>

using namespace std;

void demo1(){
    vector<int> vec={1,2,3};

    fill_n(vec.end()-1, 3, 100); //插入3个元素，每个值是100。结果后面只有1个位置，没有的位置插入失败
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl; 
}

void demo2(){
    vector<int> vec={1,2,3};

    auto it= back_inserter(vec);
    fill_n( it, 3, 100); //插入3个元素，每个值是100。成功
    for(auto ele: vec)
        cout << ele << " ";
    cout << endl; 
}


int main(){
    demo1();
    demo2();
    return 0;
}

$ g++ a12_back_inserter_fill_n.cpp 
$ ./a.out 
1 2 100 
1 2 3 100 100 100
```



#### 拷贝算法 copy

- 接收三个参数: 前2个是范围，第三个表示目的序列的起始位置。
    * 将收入范围的元素拷贝到目的序列中。
    * 重要：目的序列至少要包含与输入序列一样多的元素。

例: 使用 copy 实现内置数组的拷贝。`auto ret=copy(begin(a1), end(a1), a2); // 把a1的内容拷贝给a2`

```
#include<iostream>
using namespace std;

int main(){
    //拷贝内置数组：copy
    int a1[]={1,2,3}, len=sizeof(a1)/sizeof(*a1);
    int a2[len];

    // print
    for(auto ele: a2)
        cout << ele << " ";
    cout << endl;

    // copy
    auto ret=copy(begin(a1), end(a1), a2); // 把a1的内容拷贝给a2
    printf("&a1=%p, &a2=%p, &*ret=%p ret=%p\n", a1, a2, &*ret, ret);

    // print
    for(auto ele: a2)
        cout << ele << " ";
    cout << endl;

    cout << *(--ret) << endl;

    return 0;
}

$ g++ a13_copy.cpp
$ ./a.out 
1503212264 32621 1501466151 
&a1=0x7ffceb0397cc, &a2=0x7ffceb039760, &*ret=0x7ffceb03976c ret=0x7ffceb03976c
1 2 3 
3
```

- copy 返回值是指向其目的位置的迭代器(递增后)。即，ret恰好指向拷贝到 a2 的尾元素之后的位置。


多个算法提供所谓的 copy 版本，就是新元素放在新创建的序列中。

例: replace()接受4个参数，并将所有等于参数3的值更改为参数4，前2个是一对输入序列迭代器。

```
#include<iostream>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;

void print2(list<int> ctn){
    for(auto ele: ctn)
        cout << ele << " ";
    cout << endl;
}

void demo1(){
    list<int> ilist={1,2,3,4,2};
    //1. 把2替换为 200
    replace(ilist.begin(), ilist.end(), 2, 200);
    print2(ilist);
}

void demo2(){
    list<int> ilist={1,2,3,4,2};
    // 2. replace 的 copy 版本: 第三个参数是迭代器，指出替换后序列的保存位置
    vector<int> ivec;
    replace_copy(ilist.cbegin(), ilist.cend(), 
        back_inserter(ivec), 2, 200);
    print2(ilist); //原容器不变

    // ivec 是ilist 的拷贝，并做了修改
    for(auto ele: ivec)
        cout << ele << " ";
    cout << endl;

}

int main(){
    demo1();
    demo2();

    return 0;
}

$ g++ a14_replace.cpp 
$ ./a.out 
1 200 3 4 200 
1 2 3 4 2 
1 200 3 4 200
```





### 10.2.3 重排容器元素的算法

sort 会重排元素的值，是调用 `<` 运算符来实现排序的。

`the quick red fox jumps over the slow red turtle`

#### 消除重复单词

- 先对vector排序 sort。
    * sort 接受2个迭代器，表示范围，对该范围内进行排序。注意 red和the各出现了2次。
- 然后执行 unique 的标准库算法来重排 vector，得到不重复的元素出现在vector的开始部分。
    * 将相邻的重复元素“删除”的只剩下一个。
    * 返回是非重复元素的下一个位置。后面的元素都还在，但是值未知。
- 然后使用容器 vector 的erase 真正删除元素。

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void print(vector<string> svec, int i=0){
    cout << i << " ";
    for(auto ele: svec)
        cout << ele<< " ";
    cout << endl;
}

int main(){
    vector<string> svec={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    print(svec);
    //1.排序: 按字典顺序升序 a-z
    sort(svec.begin(), svec.end());
    print(svec,1);
    //2.unique 重排，每个单词只出现一次；返回值是迭代器，指向unique区域之后的一个位置
    auto uniq_next = unique(svec.begin(), svec.end());
    print(svec,2);
    cout << *(uniq_next-1) << endl;
    
    //3.删除其余的元素
    svec.erase(uniq_next, svec.end());
    print(svec,3);
    return 0;
}


$ g++ a15_sort_unique.cpp 
$ ./a.out 
0 the quick red fox jumps over the slow red turtle 
1 fox jumps over quick red red slow the the turtle 
2 fox jumps over quick red slow the turtle the  
turtle
3 fox jumps over quick red slow the turtle
```



#### 使用容器操作删除元素

算法不能删除元素，所以调用的是容器的方法。

即使容器中没有重复项，调用也是安全的。










## 10.3 定制操作

很多算法的比较操作可以用户自定义，包括`<`或`==`等。

sort，如果想自定义顺序，或者未定义`<`运算符，则需要重载 sort 的默认行为。



### 10.3.1 向算法传递函数

sort 的第二个版本，可以接受参数3，一个谓词(predicate)。


#### 谓词

- 一元谓词 unary predicate，只接受单一参数
- 二元谓词 binary predicate，有2个参数。

例: 按长度排序
```
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// 按单词的长度排序
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

int main(){
    vector<string> svec={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    sort(svec.begin(), svec.end(), isShorter); //参数3是函数
    for(auto ele: svec)
        cout << ele << " ";
    cout << endl;
    return 0;
}

$ g++ a16_sort_fn_Para.cpp 
$ ./a.out 
the red fox the red over slow quick jumps turtle
```

结果：所有长度为3的单词都在长度为4的单词前面，然后是更长的单词。





#### 排序算法 stable_sort

等长元素怎么排序？为了保证结果的唯一性，可以使用 stable_sort ，保证等长元素的字典序。

```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void elimDups(vector<string> &svec){
    //排序
    sort(svec.begin(), svec.end());
    //保持唯一
    auto iter=unique(svec.begin(), svec.end());
    //删除后面的重复元素
    svec.erase(iter, svec.end());
}

// 按单词的长度排序
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

int main(){
    vector<string> svec2={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    //1.按字典排序，去重
    elimDups(svec2);
    for(auto ele: svec2)
        cout << ele << " ";
    cout << endl;

    //2. 按长度排序，长度相同的保持字典序
    stable_sort(svec2.begin(), svec2.end(), isShorter);
    for(const auto &s: svec2) //无需拷贝字符串
        cout << s << " ";
    cout << endl;

    return 0;
}

$ g++ a17_stable_sort.cpp 
$ ./a.out 
fox jumps over quick red slow the turtle 
fox red the over slow jumps quick turtle
```





### 10.3.2 lambda 表达式

例: 只打印大于某个长度的单词。

- 使用朴素方法，for循环后直接使用 `ele.size() > 4` 判断长度
- find_if()函数
    * 接受3个参数，前2个是一对迭代器，参数3是一个一元谓词。
    * 返回迭代器，指向第一个非0值(就是找到符合要求的元素了)；如果都是0，则指向尾后位置

```
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void elimDups(vector<string> &svec){
    //排序
    sort(svec.begin(), svec.end());
    //保持唯一
    auto iter=unique(svec.begin(), svec.end());
    //删除后面的重复元素
    svec.erase(iter, svec.end());
}

// 按单词的长度排序
bool isShorter(const string &s1, const string &s2){
    return s1.size() < s2.size();
}

void bigger(vector<string> &words, vector<string>::size_type sz){
    //字典排序，去重
    elimDups(words); 
    //按长度排序，等长度的按字典排序
    stable_sort(words.begin(), words.end(), isShorter);
    //打印大于某个长度的单词
    for(auto ele: words){
        if(ele.size() > sz){
            cout << ele<< " ";
        }
    }
    cout << endl;
}

vector<string> svec2={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

void demo1(){
    bigger(svec2, 4);
}


// 定义一元谓词，作为 find_if() 的参数3
bool biggerThan4(string s2){
    return s2.size() >4;
}

void demo2(){
    for(auto ele: svec2)
        cout << ele << " ";
    cout << endl;
    // 获取长度大于n的单词
    // find_if 的3个参数，前2个是一对迭代器，参数3是一个一元谓词。
    //      返回迭代器，指向第一个非0值(就是找到符合要求的元素了)；如果都是0，则指向尾后位置
    auto iter_end=find_if(svec2.begin(), svec2.end(), biggerThan4);
    cout << *iter_end << endl;
    // 打印从头到这个迭代器之前的元素
    for(auto iter=svec2.begin(); iter!=iter_end; iter++)
        cout << *iter <<" ";
    cout << endl;
}

int main(){
    demo1();
    demo2();
    return 0;
}


$ g++ a18_find_if.cpp 
$ ./a.out 
jumps quick turtle 
fox red the over slow jumps quick turtle 
jumps
fox red the over slow
```

如果想传入一个长度参数怎么办？



#### 介绍 lambda

对于一个对象或表达式，如果可以对其使用调用运算符`()`(P21,1.5.2)，则称它为可调用的。

- 我们可以向算法传递任何类型的 `可调用对象(callable object)`。
- 如果e是一个可调用的表达式，则可以写 `e(args)`，其中args是一个逗号分割的一个或多个参数的列表。
- 共4种可调用对象:
    * 目前学过的可调用对象：函数和函数指针。
    * 重载了函数调用运算符的类(P506, 14.8)
    * lambda 表达式(lambda expression)


- labmda 表达式可以理解为 未命名的内联函数。
- 和任何函数类似，一个 lambda 表达式具有一个返回类型，一个参数列表和一个函数体。
    * 但是 lambda可能定义在函数内部。
- 定义方式: `[capture list](parameter list) -> return type{function body}`
    * capture list(捕获列表)是一个 lambda 所在函数中定义的局部变量的列表(通常为空)
    * return type, parameter list 和 function body 与任何普通函数一样，分别表示返回类型，参数列表和函数体。
    * 但是，lambda 表达式必须使用 `尾置返回`来指定返回类型(P206, 6.3.3)

可以忽略参数列表和返回类型，但是必须永远包含捕获列表(可以为空，但是不能省略)和函数体
`auto f=[]{reutrn 10;};`

- 该可调用对象f，不接受参数，返回10.
- 忽略括号`()`和参数列表，等价于指定一个空参数列表。
- 忽略返回类型`-> return type`，lambda 根据函数体中的代码推断出返回类型：
    * 如果函数体只有一个return语句，则返回类型从返回的表达式的类型推断而来
    * 否则，返回类型为 void。

> Note: 如果lambda的函数体包含了任何单一return语句之外的内容，且未指定返回类型，则返回 void。

```
#include<iostream>
using namespace std;

int main(){
    // 定义 lambda 表达式
    auto f=[]{return 10;};
    // 调用
    cout << f() << endl;
}

$ g++ a19_lambda.cpp 
$ ./a.out 
10
```



#### 向 lambda 传递参数

> lambda 不能有默认参数(P211, 6.5.1).

例: 编写一个与 isShorter 功能等价的 lambda
```
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void elimDups(vector<string> &svec){
    //排序
    sort(svec.begin(), svec.end());
    //保持唯一
    auto iter=unique(svec.begin(), svec.end());
    //删除后面的重复元素
    svec.erase(iter, svec.end());
}

void print(vector<string> &svec){
    for(auto ele: svec)
        cout << ele << " ";
    cout << endl;
}

// lambda 表达式：函数的调用
void demo1(){
    auto f=[](const string &s1, const string &s2){
            return s1.size() < s2.size();
       };
    string a1="book", a2="boo";
    cout << f(a1, a2) << endl;
    a2="books";
    cout << f(a1, a2) << endl;
}

// 使用 lambda 表达式排序
void demo2(){
    vector<string> svec2={"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
    //1.字典排序，去重
    elimDups(svec2); 
    print(svec2);
    //2.按长度排序，等长的按字典序; 
    // 参数3: lambda 表达式 代替函数 isShorter
    stable_sort(svec2.begin(), svec2.end(),  
       [](const string &s1, const string &s2){
            return s1.size() < s2.size();
       } );
    print(svec2);
}

int main(){
    demo1();
    demo2();
    return 0;
}

$ g++ a20_lambda_isShorter.cpp 
$ ./a.out 
0
1
fox jumps over quick red slow the turtle 
fox red the over slow jumps quick turtle 
```



#### 使用捕获列表


rP373/864













































## 10.4 再探迭代器
















## 10.5 泛型算法结构

















## 10.6 特定容器算法
















## 小结

















