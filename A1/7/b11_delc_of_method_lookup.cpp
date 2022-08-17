#include<iostream>
using namespace std;

//用于类成员声明的名字查找
typedef double Money;
string bal="outside";

class Account {
public:
    Money balance(){ return bal; }
private:
    Money bal=3.14;
};

int main(){
    Account act;
    cout << act.balance() << endl;

    return 0;
}