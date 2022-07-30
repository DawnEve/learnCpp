# vsCode 使用技巧

## 1. 如何设置 vscode 的代码模板？

https://blog.csdn.net/weixin_67340472/article/details/125144237

```2022.7.29
#include<iostream>
using namespace std;

int main(){
	//
}
```


## 2.vscode 快捷键

> [ref1](https://blog.csdn.net/jiahao1186/article/details/121996966), [ref2](https://blog.csdn.net/xiao___tao/article/details/109741905)


### 生存级

- 缩进: 选中文本, `Ctrl+[` 和 `Ctrl+]` 实现文本的向左移动或者向右移动；
- 复制一行: `shift+alt+↓`
- 移动一行的位置: `alt+上下箭头`


- `shift+alt+F` 代码自动对齐





## OS 系统交互


运行系统命令 `ls`。
```
#include<iostream>
using namespace std;

int main(){
    cout << system("ls") << endl;;
    return 0;
}

$ g++ b4_system.cpp 
A1/3$ ./a.out | head
a10_string_index.cpp
a11_decimal_to_hex.cpp
a1_using.cpp
a2_string_init.cpp
```