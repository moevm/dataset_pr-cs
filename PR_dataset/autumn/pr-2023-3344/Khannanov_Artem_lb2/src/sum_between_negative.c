#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include <stdlib.h>

int sum_between_negative(int array[], int len_array) {
    int left_index = index_first_negative(array, len_array), right_index = index_last_negative(array, len_array), ret_sum = 0;

    for (int i = left_index; i < right_index; i++) ret_sum += abs(array[i]);

    return ret_sum;
}
