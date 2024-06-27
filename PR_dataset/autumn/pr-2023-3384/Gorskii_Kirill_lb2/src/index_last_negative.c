#include "index_last_negative.h"
#include <stdint.h> // SIZE_MAX

size_t index_last_negative(int* arr, size_t len) {
    for (size_t i = len; i > 0; i--) {
        if (arr[i - 1] < 0) 
            return i - 1;
    }
    
    return SIZE_MAX;
}