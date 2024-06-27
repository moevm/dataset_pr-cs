#include "index_first_negative.h"
#include <stdint.h> // SIZE_MAX

size_t index_first_negative(int* arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (arr[i] < 0)
            return i;
    }

    return SIZE_MAX;
}
