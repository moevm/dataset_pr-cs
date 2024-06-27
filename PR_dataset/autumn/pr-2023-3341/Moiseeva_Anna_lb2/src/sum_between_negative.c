
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

void sum_between_negative(int arr[], int arr_size){
    int sum = 0;
    int start = index_first_negative(arr, arr_size);
    int end = index_last_negative(arr, arr_size);
    for (int j = start; j < end; j++){
        sum = sum + abs(arr[j]);
    }
    printf(PRINT_NUM, sum);
}
