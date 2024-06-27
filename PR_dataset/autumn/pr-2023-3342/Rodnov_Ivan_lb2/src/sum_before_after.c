#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_before_after(int arr[], int n)
{
    int sum_before = 0;
    int sum_after = 0;
    int sum_before_after = 0;
    for (int i = 0; i <= index_first_zero(arr, n); i++)
    {
        sum_before += abs(arr[i]);
    }
    for (int i = n - 1; i >= index_last_zero(arr, n); i--)
    {
        sum_after += abs(arr[i]);
    }
    sum_before_after = sum_before + sum_after;
    return sum_before_after;


}
