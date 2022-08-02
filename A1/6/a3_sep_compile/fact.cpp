#include "fact.h"

int fact(int n){
    int rs=1;
    while(n>0){
        rs *= n--;
    }
    return rs;
}