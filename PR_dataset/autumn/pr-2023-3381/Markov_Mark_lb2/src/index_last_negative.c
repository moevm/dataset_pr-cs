#include "index_last_negative.h"

int index_last_negative(int arr[], int len) {
    int i = len - 1;
    while (arr[i] >= 0 && i >= 0)
        i--;
    if (arr[i] < 0) {
        return i;
    } else
        return -1;
}