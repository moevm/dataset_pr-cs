#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"

int diff(int arr[], int arr_elements_count) {
    return abs_max(arr, arr_elements_count) - abs_min(arr, arr_elements_count);
}