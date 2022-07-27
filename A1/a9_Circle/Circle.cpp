#include "Circle.h"

Circle::Circle(){
    this->r=0.5;
}

Circle::Circle(double R){
    this->r=R;
}

double Circle::Area(){
    return 3.14*r*r;
}
