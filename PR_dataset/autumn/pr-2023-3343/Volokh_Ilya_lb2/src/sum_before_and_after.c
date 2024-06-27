#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
int sum_before_and_after(int arr[], int size_now){
    int sumbefafter = 0;
    int first = 0;
    int last = 0;
    first = index_first_zero(arr, size_now);
    last = index_last_zero(arr, size_now);
    for(int i = 0; i <= first; ++i)
        sumbefafter += abs(arr[i]);
    for(int k = last; k < size_now; ++k)
        sumbefafter += abs(arr[k]);
    return sumbefafter;
}
