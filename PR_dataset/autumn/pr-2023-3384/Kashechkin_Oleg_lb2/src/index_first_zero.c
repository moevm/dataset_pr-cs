#include "index_first_zero.h"

int index_first_zero(int* arr, int len_arr) {
    int first_zero, i;

    for (i=0; i < len_arr; i++) {
        if (arr[i] == 0) {
            first_zero = i;
            break;
        }
    }
    return first_zero;
}