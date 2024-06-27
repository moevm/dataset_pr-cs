#include "sum.h"

int sum(int arr[], int arr_size)
{
    int min_arr_element = min(arr, arr_size);
    int sum_up_to_the_first_min = 0, i = 0, min = min_arr_element;

    while (arr[i] != min)
    {
        sum_up_to_the_first_min += arr[i];
        i++;
    }

    return sum_up_to_the_first_min;
}
