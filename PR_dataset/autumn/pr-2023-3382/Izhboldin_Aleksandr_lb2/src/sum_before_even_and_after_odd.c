#include <stdlib.h>

#include "sum_before_even_and_after_odd.h"
#include "index_last_odd.h"
#include "index_first_even.h"

long long sum_before_even_and_after_odd(int last_id, long long array[]){
    long long sum = 0;
    for (int i = 0; i < index_first_even(last_id, array); i++) 
        sum += llabs(array[i]);

    for (int i = index_last_odd(last_id, array); i <= last_id; i++)
        sum += llabs(array[i]);

    return sum;
}

