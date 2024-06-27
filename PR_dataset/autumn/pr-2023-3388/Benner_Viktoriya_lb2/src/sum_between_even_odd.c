#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
int sum_between_even_odd(int arr[], int size){
    int from = index_first_even(arr, size);
    int to = index_last_odd(arr, size);
    int sum = 0;
    for (int i = from; i < to; ++i){
        sum += abs(arr[i]);
    }
    return sum;
}
