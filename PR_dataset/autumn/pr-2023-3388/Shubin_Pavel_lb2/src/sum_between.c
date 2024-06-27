#include <stdio.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_abs.h"

int sum_between(int arr[], int len_arr){
    int sum = 0;
    int first = index_first_zero(arr, len_arr)+1;
    int last = index_last_zero(arr, len_arr);
    
    if (first < 0){
        return -1;
    } 
    else{
        return sum_abs(arr, first, last);
    }
}