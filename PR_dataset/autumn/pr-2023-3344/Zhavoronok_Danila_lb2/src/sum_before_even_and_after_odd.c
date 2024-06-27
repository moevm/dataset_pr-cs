#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_last_odd.h"
#include "index_first_even.h"

int sum_before_even_and_after_odd(int *array, int array_length)
{
    int sum = 0;

    int left_bound = index_last_odd(array, array_length);
    for (int i = left_bound; i < array_length; i++)
    {
        sum += abs(array[i]);
    }

    int right_bound = index_first_even(array, array_length);
    for (int i = 0; i < right_bound; i++)
    {
        sum += abs(array[i]);
    }

    return sum;
}
