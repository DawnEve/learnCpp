#include<iostream>
using namespace std;

// ErrCode 类表示不同类型的错误
class ErrCode{
    private:
        int num=0;
    public:
        ErrCode(int i){
            num=i;
        }
        string msg(){
            if(num==0){
                return "success";
            }else{
                return "InputError";
            }
        }
};

void error_msg(ErrCode e, initializer_list<string> il){
    //先打印错误
    cout << e.msg() << ": ";

    for(const auto &elem: il){
        cout << elem << " ";
    }
    cout << endl;
}

int main(){
    //测试错误信息
    string expected="hello";
    string actual;
    cout << "Please input hello, other word may produce an error message:" << endl;
    cin >> actual;

    if(expected != actual){
        error_msg(ErrCode(42), {"functionX error:", expected, actual}); //注意，字符串要写到花括号中
    }else{
        error_msg(ErrCode(0), {"functionX", "okey"}); //第一次调用传入3个值，第二次调用传入2个值
    }

    return 0;
}