#include "max.h"
#include "min.h"

int diff(int arr[], int arr_size)
{
    int d = max(arr, arr_size) - min(arr, arr_size);
    return d;
}