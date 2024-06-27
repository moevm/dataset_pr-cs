#include "index_first_zero.h"

int index_first_zero(int* array, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        if (array[i] == 0) {
            return i;
        }
    }
    return -1;
}
