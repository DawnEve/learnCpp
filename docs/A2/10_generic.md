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








rP364/864























## 10.3 定制操作
















## 10.4 再探迭代器
















## 10.5 泛型算法结构

















## 10.6 特定容器算法
















## 小结

















