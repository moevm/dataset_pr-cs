#include "index_first_even.h"

int index_first_even(int array[]) {
    int i = 0;
    while (array[i] % 2 != 0) {
        i++;
    }
    return i;
}
