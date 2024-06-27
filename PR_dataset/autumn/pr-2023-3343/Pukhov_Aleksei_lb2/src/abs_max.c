#include "abs_max.h"

int abs_max(int n, int arr[], int size)
{
    int maxim, id;
    maxim = 0;
    for (int i = 0; i < size; i++)
    {
        if (abs(arr[i]) > abs(maxim))
        {
            maxim = arr[i];
            id = i;
        }
    }
    if (n == 0)
    {
        printf("%d\n", maxim);
    }
    else if (n == 2)
    {
        return maxim;
    }
    else if (n == 3)
    {
        return id;
    }
}