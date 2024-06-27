#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum.h"
#include "sum_between.h"

unsigned long sum_between(int* array, unsigned int length) {
    int first = index_first_zero(array, length);
    int last = index_last_zero(array, length);

    return sum(array, first+1, last-1);
}
