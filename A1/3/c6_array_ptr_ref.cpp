#include<iostream>
using namespace std;

//数组的指针，数组的引用
int main(){

    int *ptrs[10]; //ptrs 是含有10个整型指针的数组
    //从右向左读：10个元素的数组，名字 ptrs，保存的是指针，指向的是int

    int arr[10]={0,1,2};
    //int &refs[10]=arr; //error: declaration of ‘refs as array of references

    int (*pArr2)[10] = &arr; //pArray 指向一个含有10个整数的数组
    // 由内向外读更好理解，按结合性顺序： 
    //    *pArr 是一个指针； 
    //    接着看右边，指向一个长度为10的数组的指针；
    //    最后观察左侧，它指向int数组；
    int (&refArr3)[10] = arr; //refArr 引用一个含有10个整数的数组
    // 同上
    // &refArr 是一个引用
    // 看右侧，引用对象是一个长度10的数组
    // 看左侧，数组中元素是int

    cout << "&arr  =  " << &arr << endl;
    cout << "pArr2  = " << pArr2 << endl;
    cout << "refArr3= " << refArr3 << endl;

    // 更复杂的用法
    int *(&arr4)[10] = ptrs; //arr4 是数组的引用，该数组含有10个指针
    // 由内向外，
    //    圆括号内 &arr4 是一个引用，
    //    看右侧，引用的是一个长度10的数组
    //    看左侧，数组的元素是指向 int 的指针

    return 0;
}