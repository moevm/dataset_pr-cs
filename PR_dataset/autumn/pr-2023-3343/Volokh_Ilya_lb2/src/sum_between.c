#include <stdio.h>
#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_between(int arr[], int size_now){
    int sumbet = 0;
    int first = 0;
    int last = 0;
    first = index_first_zero(arr, size_now);
    last = index_last_zero(arr, size_now);
    for (int i = first + 1; i < last; i++) {
        sumbet += abs(arr[i]);
    }
    return sumbet;
}
