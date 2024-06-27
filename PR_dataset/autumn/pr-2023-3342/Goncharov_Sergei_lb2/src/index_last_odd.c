#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"

int index_last_odd(int array[], int array_size)
{
    for (int i = array_size - 1; i >= 0; i--)
    {
        if (array[i] % 2 != 0) 
        {
            return i;
        }
    }
    return -1;
}
