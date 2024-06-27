#include "abs_max.h"

int abs_max(int array[],int size){
    int abs_max_iterator=0;
    for(int i = 1; i < size; i++){
        if(abs(array[i]) > abs(array[abs_max_iterator])) abs_max_iterator = i;
    }
    return abs_max_iterator;
}