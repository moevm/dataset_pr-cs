#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

#define pair arr, arr_len

int sum_between(int arr[], int arr_len) {
    int sum = 0;
    int f_zero = index_first_zero(pair);
    int l_zero = index_last_zero(pair);
    int i = f_zero + 1;
    while (i < l_zero) {
        sum += abs(arr[i]);
        i++;
    }
    return sum;
}