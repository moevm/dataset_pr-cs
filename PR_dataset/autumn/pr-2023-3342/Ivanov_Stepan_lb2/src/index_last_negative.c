#include "index_last_negative.h"


int
index_last_negative(int arr[], size_t len_arr)
{
    int index = -1;
    
    for (size_t i = len_arr-1; i > 0; --i)
    {
        if (arr[i] < 0)
        {
            index = i;
            break;

        }

    }

    return index;

}

