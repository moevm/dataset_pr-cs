#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

void sum_before_and_after_negative(int arr[], int arr_size){
    int sum = 0;
    int start = index_first_negative(arr, arr_size);
    int end = index_last_negative(arr, arr_size);
    for (int j = 0; j < start; j++){
        sum = sum + abs(arr[j]);
    }
    for (int k = end; k < arr_size; k++){
        sum = sum + abs(arr[k]);
    }
    printf(PRINT_NUM, sum);
}
