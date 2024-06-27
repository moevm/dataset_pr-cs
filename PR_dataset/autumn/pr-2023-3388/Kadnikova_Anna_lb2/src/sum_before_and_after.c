#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#define ERR -1

int sum_before_and_after(int arr[], int len_arr){
    int first = index_first_zero(arr,len_arr);
    int last = index_last_zero(arr,len_arr);
    int sum = 0;
    if (first == ERR || last == ERR){
        sum = ERR;
    }
    else{
        for (int j = 0; j < first; j++){
            sum = sum + abs(arr[j]);
        }
        for (int j = last; j < len_arr; j++){
            sum = sum + abs(arr[j]);
        }
    }
    return sum;
}
