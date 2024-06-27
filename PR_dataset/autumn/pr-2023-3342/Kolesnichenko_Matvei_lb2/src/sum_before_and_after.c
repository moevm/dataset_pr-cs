#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_before_and_after(int arr[], int len_arr){
    int ans = 0;
    for (int i = 0; i < index_first_zero(arr, len_arr); ++i){
        ans = ans + abs(arr[i]);
    }
    for (int x = index_last_zero(arr,len_arr) + 1; x < len_arr; ++x){
        ans = ans + abs(arr[x]);
    }
    return ans;
}