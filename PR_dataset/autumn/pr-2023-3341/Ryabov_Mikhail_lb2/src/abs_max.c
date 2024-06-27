#include "abs_max.h"

int abs_max(int arr[], int size) {
        int max = arr[0];
        for (int i = 0; i < size; i++) {
                if (abs(max) < abs(arr[i])) {
                        max = arr[i];
                }
        }
        return max;
}

