#include<iostream>
using namespace std;

// 静态成员
class Account {
public:
    void calculate(){ amount += amount * interestRate; }
    static double rate(){ return interestRate; }
    static void rate(double);
    Account(string name, double total): owner(name), amount(total) {}
    void show(){cout << owner << ": " << amount << endl; }
private:
    std::string owner;
    double amount;

    static double interestRate;
    static double initRate();
};
// 必须初始化，否则报错
double Account::interestRate = 2.7;

int main(){
    Account a1{"Tom", 120}, *pac = &a1;
    Account &ra = a1;
    Account::rate(1.28);

    cout << "1 " << Account::rate() << endl; //调用1
    cout << "2 " << a1.rate() << endl; //等价调用2
    cout << "3 " << pac->rate() << endl; //等价调用3
    cout << "4 " << ra.rate() << endl; //等价调用4

    double r;
    r=Account::rate();
    cout << "5 " << r << endl;

    a1.calculate();
    a1.show();

    return 0;
}

void Account::rate(double newRate){
    interestRate=newRate;
}