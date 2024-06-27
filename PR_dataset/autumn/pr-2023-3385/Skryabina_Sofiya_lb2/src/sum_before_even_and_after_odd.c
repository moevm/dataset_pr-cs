#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int mas[], int len){
    int first_even = index_first_even(mas, len);
    int last_odd = index_last_odd(mas, len);
    int summa = 0;
    for(int k = 0; k<first_even; k++){
        summa += abs(mas[k]);
    }
    for(int k = last_odd; k<(len); k++){
        summa += abs(mas[k]);
    }
    return summa;
}
