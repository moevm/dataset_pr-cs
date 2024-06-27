#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int len)
{
    int return_value = 1;
    for (int i = 0; i < index_first_negative(arr, len); i++)
    {
        return_value *= arr[i];
    }

    for (int i = index_last_negative(arr, len); i < len; i++)
    {
        return_value *= arr[i];
    }

    return return_value;
}