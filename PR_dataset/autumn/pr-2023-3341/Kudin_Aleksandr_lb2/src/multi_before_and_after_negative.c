#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int array[], int size) {
    int product = 1;
    int x = index_first_negative(array, size);
    int y = index_last_negative(array, size);
    for (int i = 0; i < x; i++) {
        product *= array[i];
    }
    for (int j = y; j < size; j++) {
        product *= array[j];
    }
    return product;
}