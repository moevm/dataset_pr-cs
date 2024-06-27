#include <stdio.h>
#include "index_last_negative.h"
#include "index_first_negative.h"
#include "multi_between_negative.h"

int multi_between_negative(int arr[], size_t size) {
    size_t first_negative = index_first_negative(arr, size);
    size_t last_negative = index_last_negative(arr, size);
    if (first_negative == -1 || last_negative == -1) {
        return 0; 
    }

    int result = 1;
    for (int i = first_negative; i < last_negative; i++) {
        result *= arr[i];
    }
    return result;
}