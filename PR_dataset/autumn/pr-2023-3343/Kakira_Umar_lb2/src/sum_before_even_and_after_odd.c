#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"


int sum_before_even_and_after_odd(int array[], int index_even, int index_odd, int size){
    int sum = 0;
    for(int i = 0 ; i < index_even; ++i){
        sum += abs(array[i]);
    }
    for(int i = index_odd; i < size;++i){
        sum += abs(array[i]);
    }
    return sum;
}