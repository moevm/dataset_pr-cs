#include "abs_min.h"

int abs_min(int array[],int size){
    int abs_min_iterator=0;
    for(int i = 1; i < size; i++){
        if(abs(array[i]) < abs(array[abs_min_iterator])) abs_min_iterator = i;
    }
    return abs_min_iterator;
}