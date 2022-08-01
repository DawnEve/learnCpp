#include<iostream>
using namespace std;

// try 处理异常
int main(){
    int a, b;
    while(1){
        cout << "Please input 2 int:" << endl;
        try{
            cin >>a >> b;
            if(b==0){
                throw runtime_error("must not be devided by 0");
            }

            //如果执行到这里，说明b不等于0
            cout << a/b << endl;
        }catch (runtime_error err){
            cout << err.what()
                << "\n Try again? Enter y or n" << endl;
                char c;
                cin >> c;
                if(! cin || c=='n'){
                    break; //跳出while 循环
                }
        }
    }
    
    return 0;
}