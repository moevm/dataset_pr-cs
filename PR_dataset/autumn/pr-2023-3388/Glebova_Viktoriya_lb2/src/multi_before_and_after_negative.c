#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int *mas, int count){
    int fi = index_first_negative(mas, count);
    int la = index_last_negative(mas, count);
    int przv = 1;
    for(int i = 0; i < fi; i++){
        przv = przv * mas[i];
        
    }
    while(la < count){
        przv = przv * mas[la];
        la++;
        
    }
    return przv;
}