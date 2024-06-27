#include "index_first_negative.h"
#include "get_index.h"

int index_first_negative(int* arr, int N) {
    return get_index(0, -N, 1, arr);
}

