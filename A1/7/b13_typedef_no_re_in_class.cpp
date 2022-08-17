#include<iostream>
using namespace std;

typedef double Money;
class Account{
public:
    Money balance(){ return bal; } //使用外层作用域的 Money，且Money表示类型
    //typedef double Money; //错误: 不能重新定义 Money
    //error: declaration of ‘typedef double Account::Money’ changes meaning of ‘Money’
private:
    Money bal=10;
};

int main(){
    Account act;
    cout << act.balance() << endl;

    return 0;
}