#include "sum.h"
#include "abs_max.h"
int sum(int arr[], int len) {
    int max_val = abs_max(arr, len);
    int max_index = -1;
    for (int i = 0; i < len; i++) {
        if (arr[i] == max_val) {
            max_index = i;
            break;
        }
    }

    int sumi = 0;
    for (int i = max_index; i < len; i++) {
        sumi += arr[i];
    }

    return sumi;
}