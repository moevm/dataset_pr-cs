#include "index_first_even.h"

int index_first_even(int *array, int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
        if (array[i] % 2 == 0)
            return i;
    }

    return -1;
}
