#include <stdio.h>
#include "get_index.h"
int index_last_negative(int* arr, int N) {
    return get_index(N - 1, -1, 1, arr);
}
