#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>

int sum_before_and_after(int array[], int actual_size_of_array) {
    int sum = 0;
    for (int i = index_last_zero(array, actual_size_of_array)+ 1; i < actual_size_of_array; i++) {
        sum += abs(array[i]);
    }
    for (int i = 0; i < index_first_zero(array, actual_size_of_array); i++) {
        sum += abs(array[i]);
    }
    return sum;
}