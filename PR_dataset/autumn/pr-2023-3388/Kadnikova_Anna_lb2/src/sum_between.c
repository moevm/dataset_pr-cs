#include <stdio.h>
#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#define ERR -1

int sum_between(int arr[], int len_arr){
    int first = index_first_zero(arr,len_arr);
    int last = index_last_zero(arr,len_arr);
    int sum = 0;
    if ( first == ERR || last == ERR){
        sum = ERR;
    }
    else{
        for (int j = first; j < last; j++){
            sum = sum + abs(arr[j]);
        }
    }
    return sum;
}
