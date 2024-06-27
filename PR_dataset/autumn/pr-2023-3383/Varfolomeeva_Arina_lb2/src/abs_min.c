#include <stdlib.h>
int abs_min(int arr_int[], int count) {
    int min = 100000;
    for (int i=0; i<count; i++) {
        if (abs(arr_int[i]) < abs(min)) {
            min = arr_int[i];
        }
    }
    return min;
}