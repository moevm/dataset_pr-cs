#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"


int sum_before_even_and_after_odd(int array[], int ind_count){
    int index_first1 = index_first_even(array, ind_count);
    int sum_answer = 0;
    for(int i = 0; i < index_first1; i++){
        sum_answer+=abs(array[i]);
    }

    for(int index_last_odd1 = index_last_odd(array, ind_count); index_last_odd1 < ind_count; index_last_odd1++){
        sum_answer+=abs(array[index_last_odd1]);
    }

    return sum_answer;
}