# 2 变量和基本类型

`$ cd mkdir A1/2/`

## 内置类型

### 类型转换

```// a1_convert.cpp
#include<iostream>
int main(){
    unsigned u=10;
    int i=-42;
    std::cout << "i+i=" << i+i << std::endl; //-84
    std::cout << "i+u=" << i+u << std::endl; //4294967264
    std::cout << "u+i=" << u+i << std::endl; //4294967264
    return 0;
}
```



## 转义序列

制作一个进度条。要点: 

- 睡眠 0.1s; 
- 不换行，移动到当前行的最前面 \r


```
$ cat a2_progression.cpp
#include<iostream>
#include<string>
#include <unistd.h>
using namespace std;

// 进度条: 原生实现

int main(){
    int total=80;
    float ratio=0;
    string row=" ";
    // 百分比数字前的空格
    for(int i=0; i<=total; i++){
        row += " ";
    }

    // 显示进度条
    for(int i=0; i<=total; i++){
        string str="";
        ratio = (1.00*i)/total * 100;
        for(int j=0; j<i; j++){
            str += "=";
        }
        //1. sleep for some us; https://www.gaojiufeng.cn/?id=301
        usleep(0.05*1e6);
        //printf("%s>>\r", str.c_str() );
        //2. 只刷新缓存不换行 https://www.likecs.com/ask-152700.html
        cout << row << (int)ratio << "%\r"; 
        cout << str << "=>\r" << std::flush; 
    }
    //换行
    cout << endl;
    return 0;
}


编译执行:
$ g++ a2_progression.cpp 
$ ./a.out 
=================================================================================>100%
```







## 变量

初始化和赋值是两个完全不同的操作。区别是啥？ //todo


### 列表初始化(4种)

有四种列表初始化的方法。包括根据 C++11 新定义的花括号初始化方法。

```
#include<iostream>
using namespace std;

int main(){
    int a1=0;
    int a2={1};
    int a3{3};
    int a4(4);

    cout << "a1=" << a1 << endl;
    cout << "a2=" << a2 << endl;
    cout << "a3=" << a3 << endl;
    cout << "a4=" << a4 << endl;

    return 0;
}


$ g++ a3_init.cpp 
$ ./a.out 
a1=0
a2=1
a3=3
a4=4
```


{} 会在转换有可能损失数据的时候报错提示：
```
#include<iostream>
using namespace std;

int main(){

    long double ld=3.14159265358;
    // 错误: 转换未执行，因为存在丢失信息的风险：小数会丢失，整数可能太大丢失
    //int a1{ld}; //narrowing conversion of ‘ld’ from ‘long double’ to ‘int’
    //int a2={ld};

    // 正确：转换执行，且丢失部分数据。
    int a3(ld);
    int a4=ld;

    //cout << "a1=" << a1 << endl;
    //cout << "a2=" << a2 << endl;
    cout << "a3=" << a3 << endl;
    cout << "a4=" << a4 << endl;

    return 0;
}
```


### 默认初始化

函数内的内置类型变量将 不被初始化。里面的值是随机的，访问将引发程序错误。


```
#include<iostream>
using namespace std;

int add(int x, int y){
    int b;
    cout << "para in function, not init: " << b << endl;
    return x+y;
}

int main(){
    int a;
    cout << a << endl; //0
    cout << add(1,5) << endl; //不确定函数内的b的值
    return 0;
}


$ g++ a3_init3.cpp

$ ./a.out 
0
para in function, not init: 32664
6

$ ./a.out 
0
para in function, not init: 32745
6
```




## 声明与定义变量

声明是为了多个文件共用变量。

只声明，则使用 extern 关键字。

而定义变量，则同时申请内存空间。

extern 如果包含了初始值，则不再是声明，而是定义。

> 变量能且只能被定义一次，但是可以多次被声明。



