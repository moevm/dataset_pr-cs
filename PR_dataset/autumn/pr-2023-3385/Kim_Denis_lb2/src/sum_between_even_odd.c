#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int *array, int size_array){
    int first_index = index_first_even(array, size_array);
    int last_index = index_last_odd(array, size_array);
    int abs_sum_between = 0;
    for(int i = first_index; i < last_index; i++){
        abs_sum_between = abs_sum_between + abs(array[i]);
    }
    return abs_sum_between;
}
