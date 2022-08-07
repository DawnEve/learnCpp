#include<iostream>
using namespace std;

//根据计数器，返回单复数
string make_plural(size_t ctr, const string &word, const string &ending){
    return (ctr>1) ? word+ending : word;
    //该函数的返回值是string，意味着返回值将被拷贝到调用点。
    //因此，该函数将返回word的副本或者一个未命名的临时string对象，该对象的内容是 word 和 ending 的和。
}

//如果函数返回一个引用，则该引用仅是它所引用对象的一个别名。
//返回string对象中较短的那个
const string &shorterString(const string &s1, const string &s2){
    return s1.size() <= s2.size() ? s1 : s2;
    // 形参和返回类型都是 const string 引用，不管是调用函数还是返回结果都不会真正拷贝string 对象
}


int main(){
    string s1="hi";
    string s2="dog";
    string ending="s";

    //返回拷贝，则地址改变
    string s3=make_plural(3, s2, ending);
    string s4=make_plural(1, s2, ending);
    cout << "addr: &s2=" << &s2 << ", value s2=" << s2 << endl;
    cout << "addr: &s3=" << &s3 << ", value s3=" << s3 << endl;
    cout << "addr: &s4=" << &s4 << ", value s4=" << s4 << endl;
    cout << endl;

    // 传入引用，返回引用，如果用同类型接收返回值，则地址不变
    const string &s5=shorterString(s1, s2); //必须使用相同的类型接收返回值(const + &)，否则还可能继续拷贝变量（string s5 OR const string s5）
    cout << "addr: &s1=" << &s1 << ", value s1=" << s1 << endl;
    cout << "addr: &s5=" << &s5 << ", value s5=" << s5 << endl;

    return 0;
}