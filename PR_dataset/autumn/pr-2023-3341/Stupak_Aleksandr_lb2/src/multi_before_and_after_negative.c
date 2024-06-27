#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int i) {
    int multi = 1;
    for(int k = 0; k < index_first_negative(arr, i); k++){
        multi *= arr[k];
    }
    for(int k = index_last_negative(arr, i); k < i; k++){
        multi *= arr[k];
    }
    return multi;
}