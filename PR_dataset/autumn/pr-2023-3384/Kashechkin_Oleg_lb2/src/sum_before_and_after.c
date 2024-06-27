#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_before_and_after(int* arr, int len_arr) {
    int i, sum = 0;
    int first_zero = index_first_zero(arr, len_arr);
    int last_zero = index_last_zero(arr, len_arr);

    for (i = 0; i < first_zero; i ++) {
        sum += abs(arr[i]);
    }

    for (i = last_zero; i < len_arr; i++) {
        sum += abs(arr[i]);
    }

    return sum;
}