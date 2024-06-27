#include <stdio.h>
#include "index_last_zero.h"
int indexLastZero(int array[], int lenghtArray){
    for (int i=lenghtArray-1; i>=0; i--){
        if (array[i] == 0) return i;
    }
    return -1;
}

