#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>

int sum_before_and_after_negative(int arr[], int N){
    int sum_all = 0;
    for (int i = 0; i < index_first_negative(arr, N); i++){
        sum_all += abs(arr[i]);
    }
    for (int i = index_last_negative(arr, N); i < N; i++){
        sum_all += abs(arr[i]);
    }
    return sum_all;
}