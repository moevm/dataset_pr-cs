#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_between(int array[], int array_size){
        int summary = 0;
        for(int i = index_first_zero(array, array_size) + 1; i < index_last_zero(array, array_size); i++){
                summary += abs(array[i]);
        }
        return summary;
}
