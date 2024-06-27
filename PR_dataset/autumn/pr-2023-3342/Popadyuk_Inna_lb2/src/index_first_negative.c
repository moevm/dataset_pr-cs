#include <stdio.h>
#include "index_first_negative.h"

int index_first_negative(int arr[], size_t size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1; 
}