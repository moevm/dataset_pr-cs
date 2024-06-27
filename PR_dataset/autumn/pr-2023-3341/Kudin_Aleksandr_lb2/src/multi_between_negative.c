#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int array[], int size) {
    int start_of_negative = index_first_negative(array, size);
    int end_of_negative = index_last_negative(array, size);
    int product = 1;
    for (int i = start_of_negative; i < end_of_negative; i++) {
        product *= array[i];
    }
    return product;
}
