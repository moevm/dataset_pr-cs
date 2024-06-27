#include "multi_before_and_after_negative.h"


int
multi_before_and_after_negative(int arr[], size_t len_arr)
{
    int mult = 1;
    int l_index = index_first_negative(arr, len_arr);
    int r_index = index_last_negative(arr, len_arr);

    for (size_t i = 1; i < l_index; ++i)
        mult *= arr[i];

    for (size_t i = r_index; i < len_arr; ++i)
        mult *= arr[i];

    return mult;

}

