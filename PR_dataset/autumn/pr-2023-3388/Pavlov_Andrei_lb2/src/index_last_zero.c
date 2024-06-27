#include "index_last_zero.h"

int index_last_zero(int* array, unsigned int length) {
    for (unsigned int i = length; i > 0; i--) {
        if (array[i-1] == 0) {
            return i - 1;
        }
    }
    return -1;
}
