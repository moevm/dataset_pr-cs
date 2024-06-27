#include <stdlib.h>
#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"

int sum_between_negative(int* array, int number_of_elements){
    int index_first = index_first_negative(array, number_of_elements);
    int index_last = index_last_negative(array, number_of_elements);
    
    int sum = 0;
    for (int i = index_first; i<index_last; i++){
        sum+= abs(array[i]);
    }
    return sum;
}