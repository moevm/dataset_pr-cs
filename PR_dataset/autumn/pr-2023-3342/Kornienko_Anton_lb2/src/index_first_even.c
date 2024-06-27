#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"

int index_first_even(int array[],int size){
    int result = - 1;
    for(int i = 0; i < size; ++i){
        if(abs(array[i]) % 2 == 0){
            result = i;
            break;
        }
    }
    return result;
}
