#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>

int sum_before_and_after(int array[], int array_size){
        int summary = 0;
        for(int i = 0; i < index_first_zero(array, array_size); i++){
                summary += abs(array[i]);
        }
        for(int i = index_last_zero(array, array_size) + 1; i < array_size; i++){
                summary += abs(array[i]);
        }
        return summary;
}
