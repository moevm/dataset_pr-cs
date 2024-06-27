#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int array[], int sizeOfArray){
    int sumOfArray = 0;
    for(int i = index_first_even(array, sizeOfArray); i < index_last_odd(array, sizeOfArray); i++){
        sumOfArray += abs(array[i]);
    }
    return sumOfArray;
}
