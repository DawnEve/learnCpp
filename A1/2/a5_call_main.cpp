#include<iostream>
using namespace std;

static int index=0;
int callMain(int x);

int main(){
    while(index < 10){
        cout << "index=" << callMain(index) << endl;
    }

    return 0;
}

int callMain(int x){
    index += 1;
    //main(); //可以调用main，但是输出结果可能不符合预期
    return index;
}