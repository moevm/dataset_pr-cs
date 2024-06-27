#include <stdio.h>
#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"


int sum_between_even_odd(int array[], int index_even, int index_odd){
    int sum = 0;
    for(int i =  index_even; i < index_odd; ++i){
        sum += abs(array[i]);
    }
    return sum;
}