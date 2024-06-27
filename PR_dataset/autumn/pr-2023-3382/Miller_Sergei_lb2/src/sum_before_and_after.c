#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_before_and_after(int m[], int lenm,  int fz, int lz) {
        int sum_bf_af = 0;
        for (int i = 0; i < fz; i++){
                sum_bf_af += abs(m[i]);
        }
        for (int i = lz; i < lenm; ++i){
                sum_bf_af += abs(m[i]);
        }
        return sum_bf_af;
}

