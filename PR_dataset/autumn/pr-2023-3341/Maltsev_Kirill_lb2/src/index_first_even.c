#include <stdlib.h>

int index_first_even(int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (abs(array[i]) % 2 == 0) return i;
    }
    return -1;
}