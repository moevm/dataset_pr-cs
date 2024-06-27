#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int arr[], int size)
{
    int index_first_negative_2 = index_first_negative(arr, size);
    int index_last_negative_2 = index_last_negative(arr, size);
    int sum_before_and_after = 0;
    int i;
    for (i = 0; i < index_first_negative_2; i++){
        sum_before_and_after += abs(arr[i]);
    }
    for (i = index_last_negative_2; i < size; i++){
        sum_before_and_after += abs(arr[i]);
    }
    return sum_before_and_after;
}  
