#include "min.h"

int min(int arr[], int arr_size)
{
    int min = arr[0], i;
    for (i = 1; i < arr_size; i++)
        if (arr[i] < min) min = arr[i];
    return min;
}
