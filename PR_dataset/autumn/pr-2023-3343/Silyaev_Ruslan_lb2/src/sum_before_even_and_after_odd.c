#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int array[], int sizeOfArray){
    int sumOfArray = 0;
    for(int i = 0; i < sizeOfArray; i++){
        if ((i < index_first_even(array, sizeOfArray)) || (i >= index_last_odd(array, sizeOfArray))) 
            sumOfArray += abs(array[i]);
    }
    return sumOfArray;
}
