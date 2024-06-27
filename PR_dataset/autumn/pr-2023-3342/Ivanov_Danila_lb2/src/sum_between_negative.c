#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include <stdlib.h>

int sum_between_negative(int arr[], int N){
    int sum = 0;
    for (int i = index_first_negative(arr, N); i < index_last_negative(arr, N); i++){
        sum += abs(arr[i]);
    }
    return sum;
}