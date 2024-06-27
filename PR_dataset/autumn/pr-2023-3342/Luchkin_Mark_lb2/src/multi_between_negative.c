#include <stdio.h>
#include "index_last_negative.h"
#include "index_first_negative.h"

int multi_between_negative(int *array, int array_size) {
    int i = index_first_negative(array, array_size);
    int result = 1;
    for (i; i < index_last_negative(array, array_size); ++i) {
        result *= array[i];
    }

    return result;
}