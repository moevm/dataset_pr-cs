#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_before_and_after(int arr[], int arrsum[], int CNT_ARR){
    int res = arrsum[CNT_ARR-1] - (arrsum[index_last_zero(arr, CNT_ARR)] - arrsum[index_first_zero(arr, CNT_ARR)]);
    return res;
}
