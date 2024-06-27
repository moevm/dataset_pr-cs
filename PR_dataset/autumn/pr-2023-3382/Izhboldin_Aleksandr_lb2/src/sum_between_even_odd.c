#include <stdlib.h>

#include "sum_between_even_odd.h"
#include "index_last_odd.h"
#include "index_first_even.h"

long long sum_between_even_odd(int last_id, long long array[]){
    long long sum = 0;
    for (int i = index_first_even(last_id, array); i < index_last_odd(last_id, array); ++i)
        sum += llabs(array[i]);

    return sum;
}
