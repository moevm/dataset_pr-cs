#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
#define N 100

int sum_before_even_and_after_odd(int *mass){
    int sum = 0, i;
    int first_even = index_first_even(mass);
    int last_odd = index_last_odd(mass);
    for(i = 0; i < N; i++){
        if(i < first_even || last_odd <= i){
            sum += abs(mass[i]);
        }
    }
    return sum; 
}
