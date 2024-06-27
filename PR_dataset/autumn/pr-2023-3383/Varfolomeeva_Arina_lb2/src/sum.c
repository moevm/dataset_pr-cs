#include "abs_max.h"
int sum(int arr_int[], int count) {
    int sum = 0, index_max_el = 0;
    int max = abs_max(arr_int, count);
    for (int i=0; i<count; i++) {
        if (arr_int[i] == max) {
            index_max_el = i;
            break;
        }
    }
    for (int i=index_max_el; i<count; i++) {
        sum += arr_int[i];
    }
    return sum;
}