#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>

int sum_before_and_after_negative(int array[], int len_array) {
    int sum_before_and_after = 0;
    int first_index = index_first_negative(array, len_array), last_index = index_last_negative(array, len_array);

    for (int i = 0; i < first_index; i++) sum_before_and_after += abs(array[i]);

    for (int i = last_index; i < len_array; i++) sum_before_and_after += abs(array[i]);

    return sum_before_and_after;
}
