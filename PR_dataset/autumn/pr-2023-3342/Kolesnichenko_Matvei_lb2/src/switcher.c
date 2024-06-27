#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"
#define OUT_PATTERN "%d\n"
void switcher(int num, int *arr, int arr_size){
    switch(num){
        case 0:
            printf(OUT_PATTERN, index_first_zero(arr, arr_size));
            break;
        case 1:
            printf(OUT_PATTERN, index_last_zero(arr, arr_size));
            break;
        case 2:
            printf(OUT_PATTERN, sum_between(arr, arr_size));
            break;
        case 3:
            printf(OUT_PATTERN, sum_before_and_after(arr, arr_size));
            break;
        default:
            printf("Данные некорректны");
            break;
    }
}