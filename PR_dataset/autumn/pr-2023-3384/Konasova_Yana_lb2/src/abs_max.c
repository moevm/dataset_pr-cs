#include "abs_max.h"
#include <stdlib.h>
int abs_max(int arr[], int len) {
    int max = abs(arr[0]);
    int rez = arr[0];
    for (int i = 1; i < len; i++) {
        int absValue = abs(arr[i]);
        if (absValue > max) {
            max = absValue;
            rez = arr[i];
        }
    }
    return rez;
}