#include "abs_min.h"

int abs_min(int n, int arr[], int size)
{
    int minimum;
    minimum = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (abs(arr[i]) < abs(minimum))
        {
            minimum = arr[i];
        }
    }
    if (n == 1)
    {
        printf("%d\n", minimum);
    }
    else if (n == 2)
    {
        return minimum;
    }
}