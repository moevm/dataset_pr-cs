#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"
#define N 100

int index_last_odd(int *mass){
    int last_odd, i;
    for(i = 0; i < N; i++){
        if(abs(mass[i]) % 2 == 1){
            last_odd = i;
        }
    }
    return last_odd;
}
