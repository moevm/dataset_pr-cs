#include <stdio.h>

int index_last_odd(int array[], int sizeOfArray){
    for(int i = 0; i < sizeOfArray; i++){
        if(array[sizeOfArray-i]%2!=0){
            return sizeOfArray-i;
        }
    }
}
