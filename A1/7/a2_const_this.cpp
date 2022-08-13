#include<iostream>
using namespace std;

// 函数参数列表后的const，要和不要有啥区别？

class A{
    public:
    int i=1;
    A(int x){ i =x;}

    void increase(int delta=1){ 
        //i+=delta; 
        this->i+=delta;
    }
    void increase2(int delta=1) const { 
        //i+=delta; //error: assignment of member ‘A::i’ in read-only object
        //this->i += delta; //error: assignment of member ‘A::i’ in read-only object

        A *this2=const_cast<A*>(this); //但是强制修改this的属性，把const去掉，就可以修改成员属性了
        // 说明函数花括号外的const确实是修饰函数内的this 的
        this2->i += delta;
    } 
    // 说明，const修饰的this，不能用于修改数据了

    int get(){ return i;}
    int get2() const { return i;} //加一个const有啥变换？
};



int main(){
    A a1(100);
    a1.increase(50);
    cout << a1.get() << endl; //A类型非常量，可以调用任何成员函数，const的和非const的
    cout << a1.get2() << endl;

    // diff? 
    A const a2(-20); //A类型常量 a2, a3, 只能调用const类型的成员函数
    const A a3(30);
    //a2.increase(); //error: passing ‘const A’ as ‘this’ argument discards qualifiers
    a2.increase2();
    //cout << a2.get() << endl; //error: passing ‘const A’ as ‘this’ argument discards qualifiers
    cout << a2.get2() << endl;

    //cout << a3.get() << endl; //error: passing ‘const A’ as ‘this’ argument discards qualifiers
    cout << a3.get2() << endl;

    return 0;
}