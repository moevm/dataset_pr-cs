#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

#ifndef stdlib
#include <stdlib.h>
#endif

int sum_between_even_odd(int array[], int count) {
    int result = 0;
    for (int i = index_first_even(array); i < index_last_odd(array, count); i++) {
        result += abs(array[i]);
    }
    return result;
}
