#include <stdio.h>
#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int mas[], int len){
    int first_even = index_first_even(mas, len);
    int last_odd = index_last_odd(mas, len);
    int summa = 0;
    for(int k = first_even; k<last_odd; k++){
        summa += abs(mas[k]);
    }
    return summa;
}
