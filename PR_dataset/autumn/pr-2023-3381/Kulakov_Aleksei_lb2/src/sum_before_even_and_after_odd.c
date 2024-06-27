#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_before_even_and_after_odd(int arr[],int k){
    int first = index_first_even(arr,k), last = index_last_odd(arr, k);
    int sum = 0;
    for (int i = 0; i < first; i++) {
        sum += abs(arr[i]);
    }
    for (int i = last; i < k; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}