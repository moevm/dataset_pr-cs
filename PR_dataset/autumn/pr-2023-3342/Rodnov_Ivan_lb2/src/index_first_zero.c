#include <stdio.h>

int index_first_zero(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if(arr[i] == 0)
        {
            return i;
        }
    }
}
