#include "diff.h"

int diff(int array[],int size){
    return array[abs_max(array,size)]-array[abs_min(array,size)];
}