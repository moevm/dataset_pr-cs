#include "multi_between_negative.h"


int
multi_between_negative(int arr[], size_t len_arr)
{
    int mult = 1;
    int l_index = index_first_negative(arr, len_arr);
    int r_index = index_last_negative(arr, len_arr);
    
    for (size_t i = l_index; i < r_index; ++i)
        mult *= arr[i];

    return mult;

}

