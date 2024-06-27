#include <stdio.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_abs.h"
#include "sum_before_and_after.h"

int sum_before_and_after(int arr[], int len_arr){
    int start_first = 0;
    int start_second = index_last_zero(arr, len_arr);
    int finish_fist = index_first_zero(arr, len_arr);
    int finish_second = len_arr - 1;
    if (start_second < 0){
        return -1;
    }
    else{
        return sum_abs(arr,start_first, finish_fist) + sum_abs(arr, start_second,finish_second);
    }

}