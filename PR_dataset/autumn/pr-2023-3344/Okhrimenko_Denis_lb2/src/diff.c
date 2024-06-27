#include "abs_max.h"
#include "abs_min.h"

int diff(int arr[], int count)
{
    int result_abs_max = abs_max(arr, count);
    int result_abs_min = abs_min(arr, count);
    int difference = result_abs_max - result_abs_min;
    return difference;
}
