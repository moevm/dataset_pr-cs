#include "abs_max.h"

int sum(int int_numbers[], int ct){
    int max_el = abs_max(int_numbers, ct);
    int index_start_of_sum = -1;
    for(int j=0; j<ct; j++){
        if(int_numbers[j] == max_el){
            index_start_of_sum = j;
            break;
        }
    }

    int summ = 0;
    for(index_start_of_sum; index_start_of_sum < ct; index_start_of_sum++){
        summ += int_numbers[index_start_of_sum];
    }

    return summ;
}
