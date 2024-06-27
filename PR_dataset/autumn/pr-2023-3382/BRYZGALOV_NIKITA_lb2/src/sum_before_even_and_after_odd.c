#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"

int sum_before_even_and_after_odd(int array[], int length){
    int j, sum1 = 0;
    for(j = 0; j < length; j++){
        if(array[j] < 0){sum1 -= array[j];
        } else {sum1 += array[j];}
    }
    sum1 -= sum_between_even_odd(array, length);
    return sum1;
}