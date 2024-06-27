#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_between(int m[], int fz, int lz) {
        int sum_btw = 0;
        for (int i = fz + 1; i < lz;  i++){
                sum_btw += abs(m[i]);
        }
        return sum_btw;
}
