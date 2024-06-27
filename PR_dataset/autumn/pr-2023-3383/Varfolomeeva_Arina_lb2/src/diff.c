#include "abs_max.h"
#include "abs_min.h"
int diff(int arr_int[], int count) {
    int max = abs_max(arr_int, count);
    int min = abs_min(arr_int, count);
    return max-min;
}