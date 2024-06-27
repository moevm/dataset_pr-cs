#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"

int index_first_even(int array[], int array_size) 
{
    for (int i = 0; i < array_size; i++) 
    {
        if (array[i] % 2 == 0) 
        {
            return i;
        }
    }
    return -1;
}
