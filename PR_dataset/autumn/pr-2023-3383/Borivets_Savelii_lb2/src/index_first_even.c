#include <stdlib.h>
#include "index_first_even.h"
int index_first_even(int mas[], int count) {
    for (int ind = 0; ind < count; ind++) {
        if (mas[ind] % 2 == 0) {
            return ind;
        }
    }
}
