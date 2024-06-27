#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#define N 100

int index_first_even(int *mass){
    int first_even, i;
    for(i = 0; i < N; i++){
        if(abs(mass[i]) % 2 == 0){
            first_even = i;
            break;
        }
    }
    return first_even;
}
