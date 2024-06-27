#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int array[], int array_size) 
{
    int first_even_index = index_first_even(array, array_size);
    int last_odd_index = index_last_odd(array, array_size);
    int sum_before = 0;
    int sum_after = 0;
    for (int i = 0; i < array_size; i++) 
    {
        if (i < first_even_index) 
        {
            sum_before += abs(array[i]);
        }
        if (i >= last_odd_index) 
        {
            sum_after += abs(array[i]);
        }
    }
    return sum_before + sum_after;
}