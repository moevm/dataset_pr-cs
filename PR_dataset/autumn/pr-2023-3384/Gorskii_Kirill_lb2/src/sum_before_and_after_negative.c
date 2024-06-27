#include "sum_before_and_after_negative.h"

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "range_abs_sum.h"

int sum_before_and_after_negative(int* arr, size_t len) {
    size_t first = index_first_negative(arr, len);
    size_t last = index_last_negative(arr, len);
    
    return calculate_range_abs_sum(arr, 0, first)
         + calculate_range_abs_sum(arr, last, len);
}