#include <stdio.h>
#include "index_last_odd.h"

int index_last_odd(int *array, int size_array){
    int odd;
    for(int i=0; i<size_array; i++){
        if(array[i]%2!=0){
            odd = i;
        }
    }
    return odd;

}
