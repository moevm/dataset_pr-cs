#include <stdio.h>

int index_first_negative(int *array, int array_size) {
    for (int i = 0; i < array_size; ++i) {
        if (array[i] < 0) {
            return i;
        }
    }
    return -1;
}