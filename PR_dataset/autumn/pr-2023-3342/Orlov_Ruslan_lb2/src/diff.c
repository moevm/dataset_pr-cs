#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"

int diff(int arr[], int size)
{
    return abs_max(arr, size) - abs_min(arr, size);
}
