#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_between(int arr[], int n)
{
    int sum_between = 0;
    for (int i = index_first_zero(arr, n); i <= index_last_zero(arr, n); i++)
    {
        sum_between += abs(arr[i]);
    }
    return sum_between;

}
