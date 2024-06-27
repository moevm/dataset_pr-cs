#include "max.h"
#include "min.h"
#include "diff.h"

int diff(int arr[], int arr_len)
{
    int diff_res;
    diff_res = max(arr, arr_len) - min(arr, arr_len);
    return diff_res;
}
