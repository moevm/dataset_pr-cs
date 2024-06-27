#include "abs_min.h"

int abs_min(int arr[], int size) {
        int min = arr[0];
        int i;
        for (i = 0; i < size; i++) {
                if (abs(min) > abs(arr[i])) {
                        min = arr[i];
                }
        }
        return min;
}

