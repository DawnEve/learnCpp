#include<iostream>
using namespace std;

//
string food="rice";

int main(){
    food += " is good";
    cout << food << endl;

    string food = "corn"; //重新定义外层定义、内层使用过的名字
    cout << food << endl;
    return 0;
}