#include "index_last_odd.h"

int index_last_odd(int array[], int count) {
    while (array[count-1] % 2 == 0) {
        count--;
    }
    return count-1;
}
