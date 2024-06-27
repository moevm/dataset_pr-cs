#include "min.h"
int sum(int arr[], int arr_size)
{
    int s = 0;
    int i = 0;
    int mn = min(arr, arr_size);
    while (arr[i] != mn)
    {
        s = s + arr[i];
        i++;
    }
    return s;
}