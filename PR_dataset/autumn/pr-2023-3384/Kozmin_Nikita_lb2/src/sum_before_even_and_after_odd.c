#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

#ifndef stdlib
#include <stdlib.h>
#endif

int sum_before_even_and_after_odd(int array[], int count) {
    int result = 0;
    for (int i = 0; i < index_first_even(array); i++) {
        result += abs(array[i]);
    }
    for (int i = index_last_odd(array, count); i < count; i++) {
        result += abs(array[i]);
    }
    return result;
}
