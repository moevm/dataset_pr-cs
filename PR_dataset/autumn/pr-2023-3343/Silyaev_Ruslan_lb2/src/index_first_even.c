#include <stdio.h>

int index_first_even(int array[], int sizeOfArray){
    for(int i = 0; i < sizeOfArray; ++i){
        if(array[i]%2==0){
            return i;
        }   
    }
}
