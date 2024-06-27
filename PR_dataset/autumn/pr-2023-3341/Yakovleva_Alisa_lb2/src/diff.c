#include "diff.h"

int diff(int arr[], int arr_size)
{
    return max(arr, arr_size) - min(arr, arr_size);
}
