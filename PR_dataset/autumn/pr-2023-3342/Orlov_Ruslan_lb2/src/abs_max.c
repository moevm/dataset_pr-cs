#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[], int size)
{
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) > abs(result))
        {
            result = arr[i];
        }
    }
    return result;
}
