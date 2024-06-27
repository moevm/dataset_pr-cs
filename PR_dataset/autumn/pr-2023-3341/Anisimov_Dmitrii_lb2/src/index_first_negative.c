#include "index_first_negative.h"

int index_first_negative(int *arr){
    int counter = 0;
    while(arr[counter] >= 0){
    counter++;
    }
    return counter;
}
