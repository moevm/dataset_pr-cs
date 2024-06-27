#include <stdlib.h>
#include "index_last_odd.h"
int index_last_odd(int mas[], int count) {
    for (int ind = count - 1; ind >= 0; ind--) {
        if (abs(mas[ind] % 2) == 1) {
            return ind;
        }
    }
}
