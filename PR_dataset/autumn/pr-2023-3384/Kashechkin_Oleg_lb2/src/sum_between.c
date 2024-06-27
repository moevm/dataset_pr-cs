#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int* arr, int len_arr) {
    int i, sum = 0;
    int first_zero = index_first_zero(arr, len_arr);
    int last_zero = index_last_zero(arr, len_arr);

    for (i = first_zero; i < last_zero; i++) {
        sum += abs(arr[i]);
    }

    return sum;
}