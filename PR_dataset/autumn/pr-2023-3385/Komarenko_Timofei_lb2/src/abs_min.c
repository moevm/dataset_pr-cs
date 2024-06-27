#include <stdlib.h>
#include <limits.h>
#include "abs_min.h"

int abs_min(int array[], int len){
    int min = abs(INT_MAX);
    for (int i=0; i<len; i++) {
        if (abs(array[i]) < abs(min)) {
            min = array[i];
        }
    }
    return min;
}
