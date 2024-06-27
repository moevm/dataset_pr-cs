#include "index_first_negative.h"

int index_first_negative(int arr[], int len) {
    int i = 0;
    while (arr[i] >= 0 && i < len)
        i++;
    if (arr[i] < 0) {
        return i;
    } else
        return -1;
}