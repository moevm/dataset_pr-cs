#include "output.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#include <stdio.h>
#define OUTPUT_STR "%d\n"

void output(int func, int arr[], int len){
    switch (func){
        case 0:
            printf(OUTPUT_STR, index_first_negative(arr, len));
            break;

        case 1:
            printf(OUTPUT_STR, index_last_negative(arr, len));
            break;
        case 2:
            printf(OUTPUT_STR, sum_between_negative(arr, len));
            break;

        case 3:
            printf(OUTPUT_STR, sum_before_and_after_negative(arr, len));
            break;
        
        default:
            printf("Данные некорректны");
            break;
    }

}