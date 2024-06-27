#include "sum_between_negative.h"

int sum_between_negative(int mas[], int ln){
    int s=0;
    for (int i=index_first_negative(mas,ln); i<index_last_negative(mas,ln); i++)
    {
        s+=abs(mas[i]);
    }
    return s;
}
