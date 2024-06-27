#include <stdlib.h>
int abs_max(int arr_int[], int count) {
    int max = -1;
    for (int i=0; i<count; i++) {
        if (abs(arr_int[i]) > abs(max)) {
            max = arr_int[i];
        }
    }
    return max;
}