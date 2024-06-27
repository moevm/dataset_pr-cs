#include <stdlib.h>
#include "abs_max.h"

int abs_max(int arr[], int arr_elements_count) {
    int max = arr[0];
    for (int j = 0; j < arr_elements_count; j++) {
        if (abs(max) < abs(arr[j]))
            max = arr[j];
    }
    return max;
}