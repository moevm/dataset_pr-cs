#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"


int sum_before_even_and_after_odd(int *array, int size_array){
    int first_index = index_first_even(array, size_array);
    int last_index = index_last_odd(array,size_array);
    int abs_sum = 0;
    for(int i =0; i < first_index; i++){
        abs_sum += abs(array[i]);
    }
    for(int i = last_index; i < size_array; i++){
        abs_sum += abs(array[i]);
    }
    return abs_sum;
}
