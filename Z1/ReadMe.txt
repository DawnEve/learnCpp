

a10 在 c++中 false 和true 各占一个字节
a11 memcpy复制string的内存会报错，在 struct 中有string时memcpy也会报错: 
    原因是string变量第一个8字节是指针，指向第一个字符。如果按位复制，析构时要free两次，导致第二次free报错。

a12 虚拟方法必须要实现吗？这里可能是gcc的一个bug？
a13 数组初始化列表中能有变量吗？


