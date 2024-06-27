#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_before_even_and_after_odd(int arr[],int k){
    int f = index_first_even(arr,k), l = index_last_odd(arr, k);
    int s = 0;
    for (int i = 0; i < f; i++) {
        s += abs(arr[i]);
    }
    for (int i = l; i < k; i++) {
        s += abs(arr[i]);
    }
    return s;
}