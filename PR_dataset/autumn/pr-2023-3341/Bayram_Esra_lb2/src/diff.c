#include "min.h"
#include "max.h"
int diff(int arr[], int size)
{
    return max(arr, size) - min(arr, size);
}