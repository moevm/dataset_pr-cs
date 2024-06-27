#include <stdlib.h>
#include "abs_max.h"

int abs_max(int array[], int len){ 
    int max_abs = 0;
    int index_max = 0;
    for (int i = 1; i < len; i++){
        if ( abs(array[i]) > abs(max_abs) ){
            max_abs = array[i];
            index_max = i;
        }
    }
    return index_max;
}
