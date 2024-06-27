#include <stdio.h>
#include "index_last_negative.h"
#include "index_first_negative.h"

int multi_before_and_after_negative(int *array, int array_size) {
    int index_last = index_last_negative(array, array_size);
    int index_frst = index_first_negative(array, array_size);
    int result = 1;
    for (int i = 0; i < array_size; ++i) {
        if ((i < index_frst) || (i >= index_last)) {
            result *= array[i];
        }
    }

    return result;
}
