#include <stdio.h>
#include "index_last_negative.h"

int index_last_negative(int arr[], size_t size) {
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1; 
}