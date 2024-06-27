#include "index_first_negative.h"


int
index_first_negative(int arr[], size_t len_arr)
{
    int index = -1;

    for (size_t i = 1; i < len_arr; ++i)
    {
        if (arr[i] < 0)
        {
            index = i;
            break;

        }

    }

    return index;

}

