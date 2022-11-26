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

    return 0;
}

$ g++ a13_copy.cpp
$ ./a.out 
1503212264 32621 1501466151 
&a1=0x7ffceb0397cc, &a2=0x7ffceb039760, &*ret=0x7ffceb03976c ret=0x7ffceb03976c
1 2 3 
```











rP368/864


































## 10.3 定制操作
















## 10.4 再探迭代器
















## 10.5 泛型算法结构

















## 10.6 特定容器算法
















## 小结

















