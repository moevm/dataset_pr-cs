#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_between(int arr[], int arrsum[], int CNT_ARR){
    int res = arrsum[index_last_zero(arr, CNT_ARR)] - arrsum[index_first_zero(arr, CNT_ARR)];
    return res;
}
