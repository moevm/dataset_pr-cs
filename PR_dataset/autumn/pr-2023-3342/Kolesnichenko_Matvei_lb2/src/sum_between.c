#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_between(int arr[], int len_arr){
    int ans = 0;
    for (int i = index_first_zero(arr, len_arr); i < index_last_zero(arr, len_arr); ++i){
        ans = ans + abs(arr[i]);
    }
    return ans;
}