#include<iostream>
using namespace std;

int main(){
    int val, curVal, count;
    while(cin >> curVal){
        count=1;
        while(cin >> val){
            if(val == curVal){
                count++;
            }else{
                cout << "Value " << curVal << " occured " << count << " times" << endl;
                curVal=val;
                count=1;
            }
        }
        cout << "Value " << curVal << " occured " << count << " times" << endl;
    }
    return 0;
}