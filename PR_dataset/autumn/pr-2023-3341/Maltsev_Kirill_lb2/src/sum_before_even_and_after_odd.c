#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"


int sum_before_even_and_after_odd(int array[], int size) {
    int sum = 0;
    for (int i = 0; i < index_first_even(array, size); i++) {
        sum += abs(array[i]);
    }
    for (int i = index_last_odd(array, size); i < size; i++) {
    	sum += abs(array[i]);
    }
    return sum;
}