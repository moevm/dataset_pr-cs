#include "get_index.h"

int get_index(int begin, int finish, int increment, int* arr) {
    for (int i = begin; i > finish; i -= increment) {
        if (arr[abs(i)] < 0) return abs(i);
    }
    return -1;
}

