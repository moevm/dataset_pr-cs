#include "sum.h"

int sum(int array[],int size){
    int summ=0;
    for(int i = abs_max(array,size); i < size; i++) summ += array[i];
    return summ;
}