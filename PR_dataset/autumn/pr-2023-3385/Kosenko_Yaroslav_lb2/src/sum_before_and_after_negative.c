#include <stdlib.h>

#include "index_first_negative.h"
#include "index_last_negative.h"

long long int sum_before_and_after_negative(int arr[], int n){
    int begin = index_last_negative(arr, n);
    int end = index_first_negative(arr, n);
    long long int sum = 0;
    for (int i = 0; i < end; i++){
        sum += abs(arr[i]);
    }
    for (int i = begin; i < n; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

