#include "max.h"

int max(int arr[], int arr_size)
{
    int max = arr[0], i;
    for (i = 1; i < arr_size; i++)
        if (arr[i] > max) max = arr[i];
    return max;
}
