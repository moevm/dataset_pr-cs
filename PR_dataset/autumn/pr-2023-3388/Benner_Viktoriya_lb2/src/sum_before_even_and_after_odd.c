#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "sum_before_even_and_after_odd.h"
int sum_before_even_and_after_odd(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < index_first_even(arr, size); ++i)
        sum += abs(arr[i]);
    for (int j = index_last_odd(arr, size); j < size; ++j)
        sum += abs(arr[j]);
    return sum;
}
