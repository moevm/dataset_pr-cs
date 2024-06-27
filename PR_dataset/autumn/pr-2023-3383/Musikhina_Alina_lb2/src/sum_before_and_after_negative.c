#include "sum_before_and_after_negative.h"

int sum_before_and_after_negative(int mas[], int ln){
    int d = 0;
    for (int i=0; i<index_first_negative(mas,ln); i++)
    {
       d+=abs(mas[i]); 
    }
    for (int i=index_last_negative(mas,ln); i<ln; i++)
    {
       d+=abs(mas[i]); 
    }
    return d;
    }
