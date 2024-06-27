#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"

int index_last_odd(int array[], int size){
    int result = -1;

    for(int i = 0; i < size; ++i){
        if(abs(array[i]) % 2 == 1){
            result = i;
        }
    }
    return result;
}
