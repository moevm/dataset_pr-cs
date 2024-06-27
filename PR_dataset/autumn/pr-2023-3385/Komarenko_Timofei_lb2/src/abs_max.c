#include <stdlib.h>
#include "abs_max.h"


int abs_max(int array[], int len){
    int max = -1;
    for (int i=0; i<len; i++) {
        if (abs(array[i]) > abs(max)) {
            max = array[i];
        }
    }
    return max;
}
