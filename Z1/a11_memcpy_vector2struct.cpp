#include<iostream>
#include<vector>
#include<cstring>

struct Book{
    std::string name;
    double price;
};
void demo1(){
    Book book1, book2;
    std::vector<Book> shelf;
    //1.给book1赋值
    book1.name="this is a book about C lang, including the main part of C and its std lib."; book1.price=40.8;
    book2.name="c++ lang"; book2.price=80.8;
    std::cout << "(1)book2: " << book2.name << ", " << book2.price << std::endl;
    //2.插入到vector后面
    shelf.push_back(book1);
    //3.把 vector[0] 按内存复制到 book2
    memcpy(&book2, &shelf[0], sizeof(Book));
    //打印出 book2;
    std::cout << "(2)book2: " << book2.name << ", " << book2.price << std::endl;
}


//辅助工具 显示一个字节的16进制
void show_byte(void *p){
    printf("[%p] ", p);
    unsigned char *pChar=(unsigned char*)p;
    // 二进制 8 位 = 1byte
    for(int i=7; i>=0; i--){
        printf("%s",  (*pChar&(1<<i))?"1":"0" );
    }
    // 16进制 2位 = 1byte
    printf(" 0x%X | %c  \n", *pChar, *pChar);
    //printf(" %c ", *pChar);
}

void show_bytes(void *p, int len){
    unsigned char *pChar1=(unsigned char *)p;
    for(int i=0; i<len; i++){
        show_byte( pChar1+i );
    }
    printf("\n");
}

void demo2(){
    int x=1;
    show_byte(&x);
}


//这个是探索案例，保留，再写个简单的
void demo3(){
    // 1.打印堆和栈的地址，做参考
    int x0=10;
    printf("stack addr: &x0=%p (x0=%d)\n", &x0, x0); //auto变量的内存地址
    int *x1=(int *)malloc(sizeof(int));
    *x1=20;
    printf(" heap addr:  x1=%p (*x1=%d)\n", x1, *x1); //heap变量的内存地址
    free(x1);
    int arr[3]={10,20,30};
    for(int i=0; i<3; i++){
        printf("%p | arr[%d]=%d\n", &arr[i], i, arr[i]); //一个int占了4个字节
    }
    printf("\n");

    // 2.获取string的地址
    std::string s1="c lang-2nd", s2="";
    // string变量的内存地址
    printf("1 addr: &s1=%p, s1=%s\n", &s1, s1.c_str()); //直接获取string变量的地址
    printf("1 addr: &s2=%p, s2=%s\n", &s2, s2.c_str()); //直接获取string变量的地址
    printf("2 addr: s1.c_str()=%p (val=%s)\n", s1.c_str(), s1.c_str());//获取string变量.c_str() C风格的地址
    printf("2 addr: s2.c_str()=%p (val=%s)\n", s2.c_str(), s2.c_str());//获取string变量.c_str() C风格的地址
    auto iter=s1.begin();
    printf("3 addr: &*iter=%p (*iter=%c)\n", &*iter, *iter); //使用迭代器获取地址

    //获取每个 字符 的位置
    const char *pStr=s1.c_str(); //不加const 报错
    for(int i=0; i<strlen(pStr); i++){
        printf("    %p | pStr[%d]=%c\n", &pStr[i], i, pStr[i]);
    }
    printf("\n");

    //3. &s2 和 s2.c_str() 之间的10个字节是什么？
    /*
    printf("\nS1:\n");
    show_bytes(&s1, 20);
    printf("\nS2:\n");
    show_bytes(&s2, 20);
    printf("\n");
    */


    // 4. 使用 memcpy 复制string：释放阶段报错
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;

    //复制前，先保存string的第一个8字节
    int a=-1, *pA=&a; //指针变量pA，准备保存&s2的前8字节
    //printf("===>1 pA=%p\n", pA);
    memcpy(&pA, &s2, sizeof(int*));
    //printf("===>2 pA=%p\n", pA); //确实复制到该指针了：&s2的前8字节
    
    //复制字符串，s1覆盖掉s2
    memcpy(&s2, &s1, sizeof(s1));

    //恢复s2的头8字节
    memcpy(&s2, &pA, sizeof(int*));

    printf("\nAfter memcpy: \n");
    /* check addr
    printf("\nafter: S1:\n");
    show_bytes(&s1, 20);
    printf("\nafter: S2:\n");
    show_bytes(&s2, 20);
    printf("\n");

    s2.clear();
    s1.clear(); //clear也不能消除错误
    */
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}

// 简短版: 如何使用 memcpy 复制 string 变量
void demo4(){
    // 按位覆盖，仅 step2: free(): invalid pointer Aborted (core dumped) ；加上step1/3则正常
    // 原因: string 的前8位是 其内部字符串保存的地址，如果按位copy，则释放时，该地址会被释放两次
    // 解决方法: 保留 string 变量的前8字节，按位覆盖后，再恢复其前8字节
    // string 变量的第二个8字节：看着像字符串长度 //todo
    std::string s1="c lang-2nd", s2="";
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;

    //step1.复制前，先保存string的第一个8字节
    int a=-1, *pA=&a; //指针变量pA，准备保存&s2的前8字节
    memcpy(&pA, &s2, sizeof(int*));

    //step2.按位复制string变量
    memcpy(&s2, &s1, sizeof(s1)); //第2个参数覆盖掉第1个，长度为第3个参数

    //step3.恢复被覆盖string s2的头8字节
    memcpy(&s2, &pA, sizeof(int*));

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}

// 测试：string 变量第二个8字节是长度，类型为long
void show1(const std::string &s){
    printf(" addr: &s=%p, s.c_str()=%p |[%ld] %s\n", &s, s.c_str(), s.size(), s.c_str());
}
void show2(const std::string &s){
    //使用 long 打印的数字太大。可能是小端，按字节倒着写的？
    //short *pL=(short *)( ((char *)&s) + 8); //获取第2个8字节的起始地址。
    long *pL=(long *)( ((char *)&s) + 8);
    printf(" read 2nd 8 bytes: %ld\n", *pL);
}

void demo5(){
    std::string s1="this is a book about C lang, including the main part of C and its std lib.", 
        s2="c++",
        s3="0123456789ABCDE",
        s4="0123456789ABCDEF";
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    std::cout << "s3: " << s3 << std::endl;
    std::cout << "s4: " << s4 << std::endl;

    //2. 打印地址: [0,15]保存在栈，则 &s 和  s.c_str() 之间差了16字节
    //size>=16的长字符串，保存在堆；则只有前16个字节使用，其余16个字节不用。
    printf("s1.capacity()=%ld\n", s1.capacity()); //开辟的地址能容纳的字符数，超了就重新开辟
    //string变量大小:32字节; 前8字节: 指向第一个字符的指针; 接着8字节:字符串长度; 其余16字节: 保存短字符串
    printf("sizeof: s1:%ld, s2:%ld\n", sizeof(s1), sizeof(s2)); 
    
    //打印地址
    printf("s1"); show1(s1);    printf("s2"); show1(s2);
    printf("s3"); show1(s3);    printf("s4"); show1(s4);

    //打印第一个8字节: 指向第一个字符的指针
    char *p1=(char *)&s1;
    printf("\np1=%p\n", p1);
    memcpy(&p1, &s1, sizeof(char*)); //string变量头8位的地址只能按位拷贝到 指针变量 p1 中
    printf("p1=%p(val=%c), s1.c_str()=%p\n", p1, *p1, s1.c_str());

    //打印第二个8字节：字符串的长度，long int
    printf("\nsizeof long: %ld\n", sizeof(long int));
    printf("  s1 size:%ld, ", s1.size()); show2(s1);   
    printf("  s2 size:%ld, ", s2.size()); show2(s2);
    printf("  s3 size:%ld, ", s3.size()); show2(s3);
    printf("  s4 size:%ld, ", s4.size()); show2(s4);
    
    printf("\n");
};

// 第二个8字节到底是啥？
void demo6(){
    std::string s1="c++", s2="this is a book about C lang, including the main part of C and its std lib.";
    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;
    printf("s1.size()=%ld, s2.size()=%ld\n", s1.size(), s2.size());
    printf("addr: &s1=%p, s1.c_str()=%p\n", &s1, s1.c_str());
    printf("addr: &s2=%p, s2.c_str()=%p\n", &s2, s2.c_str());
    printf("\n");

    //1.按字节打印前16字节
    unsigned char *pChar=(unsigned char *) &s1;
    for(int i=0; i<20; i++){
        printf("%p [%2d] 0x%x %d %c\n", (pChar+i), i, *(pChar+i), *(pChar+i), *(pChar+i) );
        if(i==7 || i==15) printf("\n");
    }

    //2.打印第二个8字节：字符串长度 s.size(), long类型
    printf("sizeof long: %ld\n", sizeof(long));
    long *pL=(long *)( ((char *)&s1) + 8);
    printf("2nd 8 bytes of s1: %ld\n", *pL);

    long *pL2=(long *)( ((char *)&s2) + 8);
    printf("2nd 8 bytes of s2: %ld\n", *pL2);
}


int main(){
    //demo1();
    //demo2();
    //demo3();
    //demo4();
    //demo5();
    demo6();

    return 0;
}