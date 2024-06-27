#include "index_first_zero.h"

int index_first_zero(int array[], int actual_size_of_array) {
    for (int i = 0; i < actual_size_of_array; i++) {
        if (array[i] == 0) {
            return i;
        }
    }
}