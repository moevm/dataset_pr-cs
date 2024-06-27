#include "index_first_zero.h"

int index_first_zero(int arr[], int size) {
    int index;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            index = i;
            break;
        }
    }
    return index;
}
