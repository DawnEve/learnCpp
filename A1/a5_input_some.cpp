#include<iostream>
using namespace std;

int main(){
    int sum=0, i=0;
    cout << "Input some numbers;" << endl;
    while(cin >> i)
        sum+=i;
    
    cout << "Sum of these values are " << sum << endl;
    return 0;
}