#include "abs_min.h"
#include <stdlib.h>
int abs_min(int arr[], int len) {
    int min = abs(arr[0]);
    int rez = arr[0];
    for (int i = 1; i < len; i++) {
        int absValue = abs(arr[i]);
        if (absValue < min) {
            min = absValue;
            rez = arr[i];
        }
    }
    return rez;
}