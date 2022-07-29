#include<iostream>

using namespace std;

struct Sales_data{
    std::string bookNo;
    unsigned units_sold=0;
    double price=0.0;

    double revenue=0.0;
}; //记得分号结尾

int main(){
    Sales_data data1, data2, *salesPtr;
    double price=0.0; //书的总价

    cout << "Input ISBN units_sold price" << endl;
    //1.读数据
    cin >> data1.bookNo >> data1.units_sold >> data1.price;
    data1.revenue = data1.units_sold * data1.price;
    //
    cin >> data2.bookNo >> data2.units_sold >> data2.price;
    data2.revenue = data2.units_sold * data2.price;

    //2.判断isbn是否相同
    if(data1.bookNo == data2.bookNo){
        //3.如果相同，则求和，输出总本书,总金额,均价。
        unsigned totalCnt=data1.units_sold+data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;
        // 输出: isbn, 总销量，中销售额，均价
        cout << data1.bookNo << "\t" << totalCnt << "\t" << totalRevenue << "\t";
        if(totalCnt!=0){
            cout << totalRevenue/totalCnt << endl;
        }else{
            cout << "No sales" << endl;
        }
        return 0;
    } else {
        cerr << "Data must refer to the same ISBN" << endl;
        return -1;
    }
}