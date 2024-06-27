#include "index_last_zero.h"

int index_last_zero(int array[], int actual_size_of_array) {
    for (int i = actual_size_of_array-1; i >= 0; i--) {
        if (array[i] == 0) {
            return i;
        }
    }
}
