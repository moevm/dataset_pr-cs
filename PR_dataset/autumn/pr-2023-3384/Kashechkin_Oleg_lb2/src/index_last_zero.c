#include "index_last_zero.h"

int index_last_zero(int* arr, int len_arr) {
    int last_zero, i;

    for (i = len_arr-1; i > 0; i--) {
        if (arr[i] == 0) {
            last_zero = i;
            break;
        }
    }
    return last_zero;
}