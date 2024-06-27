#include "range_abs_sum.h"

int calculate_range_abs_sum(int* arr, size_t first, size_t last) {
    int sum = 0;
    for (size_t i = first; i < last; i++)
        sum += abs(arr[i]);
    
    return sum;
}