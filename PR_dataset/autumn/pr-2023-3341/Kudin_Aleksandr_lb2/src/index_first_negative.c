#include "index_first_negative.h"

int index_first_negative(int array[], int size) {
    int product = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] < 0) {
            product = i;
            break;
        }
    }
    return product;
}