#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

#define pair arr, arr_len

int sum_before_and_after(int arr[], int arr_len) {
    int sum = 0;
    int f_zero = index_first_zero(pair);
    int l_zero = index_last_zero(pair);
    for (int i = 0; i < f_zero; i++) {
        sum += abs(arr[i]);
    }
    for (int i = l_zero; i < arr_len ; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}