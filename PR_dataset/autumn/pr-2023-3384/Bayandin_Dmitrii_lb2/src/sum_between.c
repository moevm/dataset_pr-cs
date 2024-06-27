#include <stdio.h>
#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_between(int quantity, int arr_end[100]){
    int sum = 0;
    int first_zero = index_first_zero(quantity, arr_end);
    int last_zero = index_last_zero(quantity - 1, arr_end);
    for (first_zero; first_zero < last_zero; ++first_zero){
        sum += abs(arr_end[first_zero]);
    }
    return sum;
}