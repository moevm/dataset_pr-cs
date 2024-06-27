#include <stdio.h>
#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int array[], int array_size) 
{
    int first_even_index = index_first_even(array, array_size);
    int last_odd_index = index_last_odd(array, array_size);
    if (first_even_index == -1 || last_odd_index == -1 || first_even_index >= last_odd_index) 
    {
        return 0;
    }
    int sum = 0;
    for (int i = first_even_index; i < last_odd_index; i++) 
    {
        sum += abs(array[i]);
    }
    return sum;
}