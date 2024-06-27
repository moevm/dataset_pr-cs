#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_between_negative(int *mas, int count){
    int fi = index_first_negative(mas, count);
    int la = index_last_negative(mas, count);
    int przv = 1;
    while(fi < la){
        przv = przv * mas[fi];
        fi++;
        
    }
    return przv;
}