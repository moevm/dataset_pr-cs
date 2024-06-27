#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after_negative.h"

int sum_before_and_after_negative(int b[], int s){
    int sum_ban = 0;
    int sba_fn;
    int sba_ln;
    sba_fn = index_first_negative(b, s);
    sba_ln = index_last_negative(b, s);
    for(int i=0;i<sba_fn;i++){
        sum_ban += abs(b[i]);
    }
    for(int i=sba_ln;i<s;i++){
        sum_ban += abs(b[i]);
    }
    return sum_ban;
}
