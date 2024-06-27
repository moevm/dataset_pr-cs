#include "sum.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

unsigned long sum_before_and_after(int* array, unsigned int length) {
    return sum(array, 0, length-1) - sum_between(array, length);
}
