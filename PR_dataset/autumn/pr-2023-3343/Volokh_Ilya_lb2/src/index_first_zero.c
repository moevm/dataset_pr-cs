#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
int index_first_zero(int arr[], int size_now) {
    int first = 0;
    int k = 0;
    while (k < size_now) {
        if (arr[k] == 0) {
            first = k;
            break;
        }
        ++k;
    }
    return first;
}
