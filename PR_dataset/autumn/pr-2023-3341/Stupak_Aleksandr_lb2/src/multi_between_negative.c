#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int i) {
    int multi = 1;
    for(int k = index_first_negative(arr, i); k < index_last_negative(arr, i); k++){
        multi *= arr[k];
    }
    return multi;
}