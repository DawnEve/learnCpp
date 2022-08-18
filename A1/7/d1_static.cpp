#include<iostream>
using namespace std;

// 静态成员

class Acount {
public:
    void calculate(){ amount += amount * interestRate; }
    static double rate(){ return interestRate; }
    static void rate(double);
    Acount(string name, double total): owner(name), amount(total) {}
private:
    std::string owner;
    double amount;

    static double interestRate;
    static double initRate();
};

int main(){
    Acount a1{"Tom", 120};
    Acount::

    double r;
    r=Account::rate(); 

    return 0;
}


void Acount::rate(double x){
    return interestRate;
}