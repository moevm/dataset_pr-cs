#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"

int sum(int arr[], int size)
{
    int max = abs_max(arr, size);
    int sum = 0;
    int found_max = 0;

    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) == abs(max))
        {
            found_max = 1;
        }

        if (found_max)
        {
            sum += arr[i];
        }
    }
    return sum;
}
