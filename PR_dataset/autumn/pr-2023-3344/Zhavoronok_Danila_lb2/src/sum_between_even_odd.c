#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int *array, int array_length)
{
    int sum = 0;

    int left_bound = index_first_even(array, array_length);
    int right_bound = index_last_odd(array, array_length);
    for (int i = left_bound; i < right_bound; i++)
    {
        sum += abs(array[i]);
    }

    return sum;
}
