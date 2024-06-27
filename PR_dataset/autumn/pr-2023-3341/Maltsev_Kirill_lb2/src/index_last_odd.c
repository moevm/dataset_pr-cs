#include <stdlib.h>

int index_last_odd(int array[], int size) {
    for (int i = size-1; i >= 0; i--) {
        if (abs(array[i]) % 2 != 0) return i;
    }
    return -1;
}