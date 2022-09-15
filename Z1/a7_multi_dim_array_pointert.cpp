#include<iostream>
using namespace std;

// 多维数组和指针
int main(){
    //part 1
    int arr[4][2]={
        {0,11},
        {22,33},
        {41,52},
        {69,78}
    };
    //print
    for(int i=0; i<4; i++){
        for(int j=0; j<2; j++){
            cout << arr[i][j] << " (" << &arr[i][j] << ")\t";
        }
        cout << endl;
    }
    cout << endl;

    //数组名 转 指针，则指向其第一个元素
    printf("arr=%p, &arr=%p, &arr[0]=%p, &arr[0][0]=%p\n", arr, &arr, &arr[0], &arr[0][0]);
    printf("arr[0][1]=%d\n", arr[0][1]);
    cout <<" >Move 8:" << "arr:" << arr << ", arr+1:" << arr+1 <<  endl; //移动了8位
    cout <<" >Move 4:"<< "arr[1]:" << arr[1] << ", arr[1]+1:" << arr[1]+1 << endl; //移动了4位
    cout << endl;
    //所以，指向该数组的指针，就是一个指向 int[2]的指针。指向数组的指针和数组名可以互换
    int (*p1)[2]=arr; //声明指向二维数组的指针，并初始哈
    printf("arr[2][1]=%d,  *(*(p1+2)+1)=%d\n", arr[2][1], *(*(p1+2)+1));
    printf(" p1[2][1]=%d, *(*(arr+2)+1)=%d\n", p1[2][1], *(*(arr+2)+1));
    //arr++; //error: lvalue required as increment operand
    cout << "before: p1:" << p1 << endl;
    p1++; //数组名不能自增，但指向该数组的指针可以自增。一次移动其子元素的大小(int[2] 2*4=8)
    cout << " incre: p1:" << p1 << ", p1[0][0]="<< p1[0][0] << endl;
    cout << "incre2: p1:" << ++p1 << ", p1[0][0]="<< p1[0][0] << endl;
    cout << "p1[-1][0]=" <<p1[-1][0] << endl; //数组下标还可以为负数，只有是有定义的合法地址
    cout << endl;

    // part 2: 指针构成的数组。
    int *parr[4][2]; //parr+1 时指针移动了多少位？
    cout << "  int:" << sizeof(int)  << endl;
    cout << " int*:" << sizeof(int*)  << endl;
    cout <<" >Move 16:" << "parr:" << parr << ", parr+1:" << parr+1 <<  endl; //移动了 int*[2]的距离: 2*8=16

    return 0;
}