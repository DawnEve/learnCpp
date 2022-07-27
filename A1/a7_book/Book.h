using namespace std;

class Book{
  private:
    string isbn="";
    float price=0;
    int num=0;

  public:
    Book(string isbn, float price, int num){
      this->isbn=isbn;
      this->price=price;
      this->num=num;
    };
    string getIsbn(){ return isbn; };
    float getPrice(){ return price; }

    // 创建加法
}; //end of class
