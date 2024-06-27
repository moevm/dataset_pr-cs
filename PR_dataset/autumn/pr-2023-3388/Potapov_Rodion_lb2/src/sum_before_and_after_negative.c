#include <stdlib.h>
#include <stdio.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int* array, int number_of_elements){
    int index_first = index_first_negative(array, number_of_elements);
    int index_last = index_last_negative(array, number_of_elements);
    
    int sum =0;
    for (int i = 0; i< index_first; i++){
        sum += abs(array[i]);
    }
    for (int i = index_last; i < number_of_elements; i++){
        sum += abs(array[i]);
    }
    return sum;
}