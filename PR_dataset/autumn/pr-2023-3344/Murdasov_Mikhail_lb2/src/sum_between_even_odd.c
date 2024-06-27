#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int array[], int ind_count){
    int index_last_odd1 = index_last_odd(array, ind_count);
    int sum_answer = 0;
    for(int index_first_even1 = index_first_even(array, ind_count); index_first_even1 < index_last_odd1; index_first_even1++){
        sum_answer+=abs(array[index_first_even1]);
    }

    return sum_answer;
}
