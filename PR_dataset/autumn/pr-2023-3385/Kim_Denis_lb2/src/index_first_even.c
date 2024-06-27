#include <stdio.h>
#include "index_first_even.h"

int index_first_even(int *array, int size_array){
    int even;
    for(int i=0; i<size_array; i++){
        if(array[i]%2==0){
            even = i;
            break;
        }
    }
    return even;
}
