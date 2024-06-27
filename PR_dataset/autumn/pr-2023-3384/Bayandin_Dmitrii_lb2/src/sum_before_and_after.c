#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_before_and_after(int quantity, int arr_end[100]){
    int sum = 0;
    int first_zero = index_first_zero(quantity, arr_end);
    int last_zero = index_last_zero(quantity - 1, arr_end);
    int k = 0;
    for (k; k <= first_zero; ++k){
        sum += abs(arr_end[k]);
    }
    for (last_zero; last_zero < quantity; ++last_zero){
        sum += abs(arr_end[last_zero]);
    }
    return sum;
}
