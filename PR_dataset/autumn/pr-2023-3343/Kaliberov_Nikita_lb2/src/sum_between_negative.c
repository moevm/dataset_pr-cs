#include <stdio.h>
#include <stdlib.h>
#include "sum_between_negative.h"

int sum_between_negative(int b[], int s){
    int sb_fn;
    int sb_ln;
    int sum_bn = 0;
    sb_fn = index_first_negative(b, s);
    sb_ln = index_last_negative(b, s);
    for(int i=sb_fn;i<sb_ln;i++){
        sum_bn += abs(b[i]);
    }
    return sum_bn;
}
