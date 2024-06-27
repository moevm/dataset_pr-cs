#include <stdlib.h>
#include "abs_min.h"

int abs_min(int arr[], int arr_elements_count) {
    int min = arr[0];
    for (int j = 0; j < arr_elements_count; j++) {
        if (abs(min) > abs(arr[j]))
            min = arr[j];
    }
    return min;
}