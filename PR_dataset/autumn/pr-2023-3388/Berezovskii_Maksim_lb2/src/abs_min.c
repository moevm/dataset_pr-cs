#include <stdlib.h>
#include <limits.h>
#include "abs_min.h"

int abs_min(int array[], int len){
    int min_abs = INT_MAX;
    int index_min = 0;
    for (int i = 1; i < len; i++){
        if (( abs(array[i]) < abs(min_abs))){
            min_abs = array[i];
            index_min = i;
        }
    }
    return index_min;
}