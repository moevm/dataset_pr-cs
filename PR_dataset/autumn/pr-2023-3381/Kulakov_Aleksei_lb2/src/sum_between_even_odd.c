#include <stdio.h>
#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int arr[],int k) {
    int first = index_first_even(arr,k), last = index_last_odd(arr,k);
    int sum = 0;
    for (int i = first; i < last; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}
