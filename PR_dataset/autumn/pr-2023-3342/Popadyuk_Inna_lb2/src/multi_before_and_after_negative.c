#include <stdio.h>
#include "index_last_negative.h"
#include "index_first_negative.h"
#include "multi_before_and_after_negative.h"


int multi_before_and_after_negative(int arr[], size_t size) {
    size_t first_negative = index_first_negative(arr, size);
    size_t last_negative = index_last_negative(arr, size);
    if (first_negative == -1 || last_negative == -1) {
        return 0; 
    }

    int result = 1;
    for (int i = 0; i < first_negative; i++) {
        result *= arr[i];
    }
    for (int i = last_negative; i < size; i++) {
        result *= arr[i];
    }

    return result;
}